/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:55:55 by alexis            #+#    #+#             */
/*   Updated: 2024/10/25 15:33:42 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*one_philo_thread(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	pthread_mutex_lock(&(data->forks[0]));
	printf("0\t1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%lld\t1 died\n", get_time_since(data->start_time));
	pthread_mutex_unlock(&(data->forks[0]));
	return (NULL);
}

void	one_philo(t_data *data)
{
	pthread_t	philo;

	if (pthread_create(&(philo), NULL, &one_philo_thread, data))
		return (perror("Thread creation error"));
	if (pthread_join(philo, NULL))
		return (perror("Thread waiting error"));
}
