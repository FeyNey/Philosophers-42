/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:09 by alexis            #+#    #+#             */
/*   Updated: 2024/10/21 19:36:13 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

//todo
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
