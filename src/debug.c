/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:32 by alexis            #+#    #+#             */
/*   Updated: 2024/10/25 15:11:29 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_data(t_data *data)
{
	printf("nb_of_philo : %i\n", data->nb_of_philo);
	printf("time_to_die : %i\n", data->time_to_die);
	printf("time_to_eat : %i\n", data->time_to_eat);
	printf("time_to_sleep : %i\n", data->time_to_sleep);
	printf("time_must_eat : %i\n", data->time_must_eat);
	printf("start time of the simulation : %lli\n", data->start_time);
}

void	print_status(char *msg, t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo->data->is_running_mutex));
	if (philo->data->is_running)
	{
		pthread_mutex_lock(&(philo->data->start_time_mutex));
		if (i == 100)
			printf(RED "%lld\t%i %s\n" RESET, get_time_since(philo->data->start_time), philo->id, msg);
		else if (i == 200)
			printf(GREEN "%lld\t%i %s\n" RESET, get_time_since(philo->data->start_time), philo->id, msg);
		else if (i == 300)
			printf(YELLOW "%lld\t%i %s\n" RESET, get_time_since(philo->data->start_time), philo->id, msg);
		else
			printf("%lld\t%i %s[%i]\n", get_time_since(philo->data->start_time), philo->id, msg, i);
		pthread_mutex_unlock(&(philo->data->start_time_mutex));
	}
	pthread_mutex_unlock(&(philo->data->is_running_mutex));
}
