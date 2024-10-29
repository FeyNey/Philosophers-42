/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:07 by alexis            #+#    #+#             */
/*   Updated: 2024/10/29 15:01:22 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*a_table(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		ft_take_forks(philo, philo->left_fork, philo->right_fork);
		ft_eat(philo);
		ft_sleep(philo);
		print_status("is thinking", philo, 300);
		i++;
		pthread_mutex_lock(&(philo->data->is_running_mutex));
		if (!philo->data->is_running)
		{
			pthread_mutex_unlock(&(philo->data->is_running_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->is_running_mutex));
		usleep(10);
	}
	return (NULL);
}

void	multiple_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	if (!data)
		return ;
	philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!philo)
		return ;
	data->is_running = 1;
	while (i < data->nb_of_philo)
	{
		init_philo(&philo[i], i, data);
		if (pthread_create(&(philo[i].thread), NULL, &a_table, &philo[i]))
		{
			ft_putstr_fd("Error creating philo thread\n", 2);
			return ;
		}
		i++;
		usleep(20);
	}
	wait_till_the_end(philo, data);
	destroy_philo_mutexes(philo, data->nb_of_philo);
	return ;
}

int	exec(t_data *data)
{
	if (data->nb_of_philo == 0)
		return (free(data), 1);
	setup_mutexes(data);
	if (data->nb_of_philo == 1)
		one_philo(data);
	else
		multiple_philo(data);
	destroy_mutexes(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (check_errors(argc, argv + 1))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	setup_arg(data, argv);
	if (data->time_must_eat == 0)
		return (free(data), 0);
	exec(data);
	return (free(data), 0);
}
