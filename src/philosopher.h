/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:16 by alexis            #+#    #+#             */
/*   Updated: 2024/10/23 21:54:20 by acoste           ###   ########.fr       */
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

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define CYAN    "\x1b[36m"
# define MAGENTA "\x1b[35m"
# define YELLOW  "\x1b[33m"
# define RESET   "\x1b[0m"

//data
typedef struct	s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				is_running;
	long long int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_running_mutex;
	pthread_mutex_t	start_time_mutex; // call it is speaking mutex ??
}					t_data;

//philo
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eaten;
	int				right_fork;
	int				left_fork;
	long long int	time_last_meal;
	pthread_mutex_t	eaten_mutex;
	pthread_mutex_t	time_last_meal_mutex;
	t_data			*data;
}				t_philo;

// main.c
int				exec(t_data *data);
void			one_philo(t_data *data);
void			multiple_philo(t_data *data);
void			*a_table(void *arg);
long long int	get_time(void);
void			ft_day(t_philo *philo, int left_fork, int right_fork);
void			ft_take_your_sit(t_philo *philo, int	left_fork, int right_fork);
void			waiting(long long time, int *is_alive, pthread_mutex_t mutex);
long long		get_time_since(long long start_time);
void			print_status(char *msg, t_philo *philo, int i);
void			*a_table(void *arg);
void			setup_default(t_data *data);

// errors.c
int				check_errors(int argc, char **argv);
int				is_not_digit(char *argv);

// utils.c
void			ft_putstr_fd(char *str, int i);
int				ft_strlen(char *str);
int				ft_atoi(char *str);

// debug.c
void			display_data(t_data *data);

// philosopher.c

//init.c
void			setup_mutexes(t_data *data);
void			setup_arg(t_data *data, char **argv);
int				destroy_mutexes(t_data *data);
void			init_philo(t_philo *philo, int i, t_data *data);

//time.c
long long		gtd(long long start_time);
long long		get_time(void);
#endif