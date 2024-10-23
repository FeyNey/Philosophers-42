/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:09 by alexis            #+#    #+#             */
/*   Updated: 2024/10/23 17:24:34 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	setup_default(t_data *data)
{
	struct timeval time;

	data->nb_of_philo = 5;
	data->time_to_die = 100;
	data->time_to_eat = 350;
	data->time_to_sleep = 500;
	data->time_must_eat = -1;
	if (gettimeofday(&time, NULL) == -1)
		return(perror("gettimeofday error\n"));
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	display_data(data);
	write (1, "\n", 1);
}

void	setup_arg(t_data *data, char **argv)
{
	struct	timeval	time;

	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->time_must_eat = ft_atoi(argv[5]);
	else
		data->time_must_eat = -1;
	if (gettimeofday(&time, NULL) == -1)
		return(perror("gettimeofday error\n"));
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
}

void	setup_mutexes(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_init(&(data->start_time_mutex), NULL);
	pthread_mutex_init(&(data->is_running_mutex), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->forks)
		return ;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	return ;
}

void	init_philo(t_philo *philo, int i, t_data *data)
{
	philo->id = i + 1;
	philo->eaten = 0;
	philo->time_last_meal = get_time();
	philo->data = data;
	pthread_mutex_init(&(philo->eaten_mutex), NULL);
	pthread_mutex_init(&(philo->time_last_meal_mutex), NULL);
}

int	destroy_mutexes(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&(data->is_running_mutex));
	pthread_mutex_destroy(&(data->start_time_mutex));
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
	return (0);
}
