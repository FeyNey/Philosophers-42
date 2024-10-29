/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:09 by alexis            #+#    #+#             */
/*   Updated: 2024/10/29 14:57:32 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	setup_arg(t_data *data, char **argv)
{
	struct timeval	time;

	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->time_must_eat = ft_atoi(argv[5]);
	else
		data->time_must_eat = -1;
	if (gettimeofday(&time, NULL) == -1)
		return (perror("gettimeofday error\n"));
	data->start_time = get_time();
}

void	init_philo(t_philo *philo, int i, t_data *data)
{
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = i + 1;
	if (philo->right_fork == data->nb_of_philo)
		philo->right_fork = 0;
	philo->eaten = 0;
	philo->time_last_meal = get_time();
	philo->data = data;
	pthread_mutex_init(&(philo->eaten_mutex), NULL);
	pthread_mutex_init(&(philo->time_last_meal_mutex), NULL);
}

void	setup_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(data->is_running_mutex), NULL);
	pthread_mutex_init(&(data->start_time_mutex), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(data->is_running_mutex));
	pthread_mutex_destroy(&(data->start_time_mutex));
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
}

void	destroy_philo_mutexes(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
		{
			ft_putstr_fd("Error : waiting thread finishes\n", 2);
			return ;
		}
		pthread_mutex_destroy(&(philo[i].eaten_mutex));
		pthread_mutex_destroy(&(philo[i].time_last_meal_mutex));
		i++;
	}
	free(philo);
}
