/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:48:35 by acoste            #+#    #+#             */
/*   Updated: 2024/10/29 15:00:27 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_wait(long long time, t_data *data)
{
	long long	start_time;

	start_time = get_time();
	while (get_time_since(start_time) < time)
	{
		pthread_mutex_lock(&(data->is_running_mutex));
		if (!data->is_running)
		{
			pthread_mutex_unlock(&(data->is_running_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(data->is_running_mutex));
		usleep(10);
	}
	return (0);
}

void	ft_take_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		print_status("has taken a fork", philo, 300);
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		print_status("has taken a fork", philo, 300);
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		print_status("has taken a fork", philo, 300);
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		print_status("has taken a fork", philo, 300);
	}
}

void	ft_eat(t_philo *philo)
{
	print_status("is eating", philo, 200);
	pthread_mutex_lock(&(philo->eaten_mutex));
	philo->eaten++;
	pthread_mutex_unlock(&(philo->eaten_mutex));
	pthread_mutex_lock(&(philo->time_last_meal_mutex));
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&(philo->time_last_meal_mutex));
	ft_wait(philo->data->time_to_eat, philo->data);
}

void	ft_sleep(t_philo *philo)
{
	print_status("is sleeping", philo, 100);
	pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
	ft_wait(philo->data->time_to_sleep, philo->data);
}

void	ft_died(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&(philo->time_last_meal_mutex));
	pthread_mutex_lock(&(data->is_running_mutex));
	data->is_running = 0;
	pthread_mutex_unlock(&(data->is_running_mutex));
	usleep(100);
	pthread_mutex_lock(&(philo->data->start_time_mutex));
	printf(RED "%lld\t%d %s\n" RESET, get_time_since(philo->data->start_time), \
			philo->id, "died");
	pthread_mutex_unlock(&(philo->data->start_time_mutex));
}
