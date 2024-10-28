/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:07 by alexis            #+#    #+#             */
/*   Updated: 2024/10/28 22:18:49 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_take_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		printf(RED "fork nb [%i] Locked by | %i |\n" RESET, left_fork, philo->id);
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		printf(RED "fork nb [%i] Locked by | %i |\n" RESET, right_fork, philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		printf(CYAN "fork nb [%i] Locked by | %i |\n" RESET, right_fork, philo->id);
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		printf(CYAN "fork nb [%i] Locked by | %i |\n" RESET, left_fork, philo->id);
	}
}

void	ft_eat(t_philo *philo)
{
	print_status("philosopher eating", philo, 300);
	pthread_mutex_lock(&(philo->eaten_mutex));
	philo->eaten++;
	pthread_mutex_unlock(&(philo->eaten_mutex));
	pthread_mutex_lock(&(philo->time_last_meal_mutex));
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&(philo->time_last_meal_mutex));
	ft_usleep((philo->data->time_to_eat));
	pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
	printf(BGRN "fork number [%i] given\n" RESET, philo->left_fork);
	pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
	printf(BGRN "fork number [%i] given\n" RESET, philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->start_time_mutex));
	printf(BBLU "%lld\trompiche de ZINZIN -> [ %i ]\n" RESET, get_time_since(philo->data->start_time), philo->id);
	pthread_mutex_unlock(&(philo->data->start_time_mutex));
	ft_usleep(philo->data->time_to_sleep);
}

void	*a_table(void *arg)
{
	t_philo	*philo;
	int i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		ft_take_forks(philo, philo->left_fork, philo->right_fork);
		ft_eat(philo);
		ft_sleep(philo);
		printf("this boy is thinking about\n");
		i++;
		pthread_mutex_lock(&(philo->data->is_running_mutex));
		if (!philo->data->is_running)
			break;
		pthread_mutex_unlock(&(philo->data->is_running_mutex));
		usleep(10);
	}
	return (NULL);
}

void	ft_died(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&(philo->time_last_meal_mutex));
	pthread_mutex_lock(&(data->is_running_mutex));
	data->is_running = 0;
	pthread_mutex_unlock(&(data->is_running_mutex));
	usleep(100);
	pthread_mutex_lock(&(philo->data->start_time_mutex));
	printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
			philo->id, "died");
	pthread_mutex_unlock(&(philo->data->start_time_mutex));
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
			if (data->time_must_eat != -1 && philo[i].eaten < data->time_must_eat)
			{
				all_eat_enought = 0;
			}
			pthread_mutex_unlock(&(philo[i].eaten_mutex));
			pthread_mutex_lock(&(philo[i].time_last_meal_mutex));
			if (get_time_since(philo[i].time_last_meal) > data->time_to_die)
			{
				printf(BRED "\n\nTIME TO DIE : [ %i ]\n\n\n" RESET, philo[i].data->time_to_die);
				printf(BBLU "\n\nTIME LAST MEAL  : %lld , my id : [ %i ]\n\n\n" RESET, get_time_since(philo[i].time_last_meal), philo[i].id);
				return (ft_died(data, &(philo[i])));
			}
			pthread_mutex_unlock(&(philo[i].time_last_meal_mutex));
			i++;
		}
		if ((all_eat_enought == 1) && data->time_must_eat != -1)
		{
			pthread_mutex_lock(&(data->is_running_mutex));
			data->is_running = 0;
			pthread_mutex_unlock(&(data->is_running_mutex));
			return ;
		}
	}
}

void	multiple_philo(t_data *data)
{
	int	i;
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
	// ft_usleep(3000000);
	wait_till_the_end(philo, data);
	// destroy_philo_mutexes(philo, data->nb_of_philo);
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
