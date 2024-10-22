/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:07 by alexis            #+#    #+#             */
/*   Updated: 2024/10/22 14:40:31 by acoste           ###   ########.fr       */
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
	printf("%lld\t1 died\n", get_time_diff(data->start_time));
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

void	ft_day(t_philo *philo, int left_fork, int right_fork)
{
	while (1)
	{
		ft_eat(philo, left_fork, right_fork);
		ft_sleep(philo);
		ft_think(philo, left_fork, right_fork);
	}
}

void	*a_table(void *arg)
{
	t_philo	*philo;
	int left_fork;
	int right_fork;

	philo = (t_philo *)arg;
	left_fork = philo->id;
	right_fork = philo->id + 1;
	if (right_fork == philo->data->nb_of_philo)
		right_fork = 0;
	ft_day(philo, left_fork, right_fork);
	return (NULL);
}

void	multiple_philo(t_data *data)
{
	int i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!philo)
		return ;
	while (i < data->nb_of_philo)
	{
		init_philo(&(philo[i]), i, data);
		if (pthread_create(&(philo[i].thread), NULL, &a_table, &(philo[i])))
			return (perror("Error Creating Thread\n"));
		usleep(200);
		i++;
	}
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

int main(int argc, char **argv)
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
