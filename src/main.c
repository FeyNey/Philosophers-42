/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:07 by alexis            #+#    #+#             */
/*   Updated: 2024/10/21 19:39:56 by acoste           ###   ########.fr       */
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

void	*prog()
{
	int i;

	i = 0;
	i++;
	printf("print i : %i", i);
	return (NULL);
}


void	multiple_philo(t_data *data)
{
	(void)data;
}
