/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:16 by alexis            #+#    #+#             */
/*   Updated: 2024/10/21 19:40:23 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

//data
typedef struct	s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	long long int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_running_mutex;
	pthread_mutex_t	start_time_mutex;
}					t_data;

//philo
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eaten;
	long long int	time_last_meal;
	pthread_mutex_t	eaten_mutex;
	pthread_mutex_t	time_last_meal_mutex;
	t_data			*data;
}				t_philo;

// main.c
int		exec(t_data *data);
void	one_philo(t_data *data);
void	multiple_philo(t_data *data);
void	*prog();

// errors.c
int	check_errors(int argc, char **argv);
int	is_not_digit(char *argv);

// utils.c
void	ft_putstr_fd(char *str, int i);
int		ft_strlen(char *str);
int		ft_atoi(char *str);

// debug.c
void	display_data(t_data *data);

// philosopher.c

//init.c
void	setup_mutexes(t_data *data);
void	setup_arg(t_data *data, char **argv);
int		destroy_mutexes(t_data *data);

//time.c
long long get_time_diff(long long start_time);

#endif