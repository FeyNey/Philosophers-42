/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:26:08 by acoste            #+#    #+#             */
/*   Updated: 2024/10/29 15:01:17 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	stop_running(t_data *data)
{
	pthread_mutex_lock(&(data->is_running_mutex));
	data->is_running = 0;
	pthread_mutex_unlock(&(data->is_running_mutex));
}

void	wait_till_the_end(t_philo *philo, t_data *data)
{
	int	i;
	int	all_eat_enought;

	while (1)
	{
		all_eat_enought = 1;
		i = 0;
		while (i < data->nb_of_philo)
		{
			pthread_mutex_lock(&(philo[i].eaten_mutex));
			if (data->time_must_eat != -1
				&& philo[i].eaten < data->time_must_eat)
				all_eat_enought = 0;
			pthread_mutex_unlock(&(philo[i].eaten_mutex));
			pthread_mutex_lock(&(philo[i].time_last_meal_mutex));
			if (get_time_since(philo[i].time_last_meal) > data->time_to_die)
				return (ft_died(data, &(philo[i])));
			pthread_mutex_unlock(&(philo[i].time_last_meal_mutex));
			i++;
		}
		if ((all_eat_enought == 1) && data->time_must_eat != -1)
			return (stop_running(data));
	}
}

long long	get_time_since(long long start_time)
{
	long long	time;

	time = get_time();
	return (time - start_time);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}
