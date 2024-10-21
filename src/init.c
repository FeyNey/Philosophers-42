/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:39:09 by alexis            #+#    #+#             */
/*   Updated: 2024/10/16 15:44:15 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	setup_arg(t_data *data, char **argv)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_must_eat = ft_atoi(argv[5]);
	else
		data->nbr_must_eat = -1;
}

void	init_mutex(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_init(&(data->is_running_mutex), NULL);
	pthread_mutex_init(&(data->forks), NULL);
}

// fork pas bon;

/*
void	init_philo(t_philo *philo)
{

}
*/