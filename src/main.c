/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:07 by alexis            #+#    #+#             */
/*   Updated: 2024/10/23 17:31:20 by acoste           ###   ########.fr       */
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
	printf("%lld\t1 died\n", gtd(data->start_time));
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

void	print_status(char *msg, t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo->data->is_running_mutex));
	if (philo->data->is_running)
	{
		pthread_mutex_lock(&(philo->data->start_time_mutex));
		printf("%lld\t%i %s[%i]\n", gtd(philo->data->start_time), philo->id, msg, i);
		pthread_mutex_unlock(&(philo->data->start_time_mutex));
	}
	pthread_mutex_unlock(&(philo->data->is_running_mutex));
}

long long	get_time_since(long long start_time)
{
	long long time;

	time = get_time();
	return (time - start_time);
}

void	waiting(long long time, int *is_alive, pthread_mutex_t mutex)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time_since(start_time)) < time)
	{
		pthread_mutex_lock(&mutex);
		if (!is_alive)
		{
			pthread_mutex_unlock(&mutex);
			return ;
		}
		pthread_mutex_unlock(&mutex);
	}
}

void	ft_eat(t_philo *philo, int	left_fork, int right_fork)
{
	if ((philo->id % 2) == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		print_status("has taken a fork", philo, left_fork);
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		print_status("has taken a fork", philo, right_fork);
		print_status("is eating", philo, 0);
		waiting(philo->data->time_to_eat, &(philo->data->is_running), philo->eaten_mutex);
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
	}
	else
	{
		// usleep(philo->data->time_to_eat / 2);
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		print_status("has taken a fork", philo, left_fork);
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		print_status("has taken a fork", philo, right_fork);
		print_status("is eating", philo, 0);
		waiting(philo->data->time_to_eat, &(philo->data->is_running), philo->eaten_mutex);
	}
}

void	ft_day(t_philo *philo, int left_fork, int right_fork)
{
	while (1)
	{
		ft_eat(philo, left_fork, right_fork);
		// ft_sleep(philo);
		// ft_think(philo, left_fork, right_fork);
	}
}

void	*a_table(void *arg)
{
	t_philo	*philo;
	int left_fork;
	int right_fork;

	philo = (t_philo *)arg;
	philo->data->is_running = 1;
	left_fork = philo->id - 1;
	right_fork = philo->id;
	print_status("<- thread lunch /", philo, 0);
	if (right_fork == philo->data->nb_of_philo)
		right_fork = 0;
	// printf("philo id : %i, left fork : %i, right fork : %i\n", philo->id, left_fork, right_fork);
	while (1)
	{
		ft_day(philo, left_fork, right_fork);
	}
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
		i++;
	}
	usleep(2000000);
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
	if (argc == 1)
	{
		printf("Tes arguments du con\n");
		return (0);
	}
	if (argv[1][0] != 'd')
		if (check_errors(argc, argv + 1))
			return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argv[1][0] != 'd')
		setup_arg(data, argv);
	if (argv[1][0] != 'd')
		if (data->time_must_eat == 0)
			return (free(data), 0);
	if (argv[1][0] == 'd')
		setup_default(data);
	exec(data);
	return (free(data), 0);
}
