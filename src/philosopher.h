/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:16 by alexis            #+#    #+#             */
/*   Updated: 2024/10/28 21:51:41 by acoste           ###   ########.fr       */
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

# define BLU     "\e[0;34m"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define CYAN    "\x1b[36m"
# define MAGENTA "\x1b[35m"
# define YELLOW  "\x1b[33m"
# define RESET   "\x1b[0m"

# define BRED    "\e[1;31m"
# define BGRN    "\e[1;32m"
# define BBLU    "\e[1;34m"

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

//debbug.c
void		display_data(t_data *data);
void		print_status(char *msg, t_philo *philo, int i);

//errors.c
int			is_not_digit(char *argv);
int			check_errors(int argc, char **argv);

//init.c
void		setup_default(t_data *data);
void		setup_arg(t_data *data, char **argv);
void		setup_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);
void		init_philo(t_philo *philo, int i, t_data *data);
void		destroy_philo_mutexes(t_philo *philo, int nb_philo);
void		wait_till_the_end(t_philo *philo, t_data *data);

//main.c
int			exec(t_data *data);
void		multiple_philo(t_data *data);
void		*a_table(void *arg);

//orders.c
void		ft_wait(long long time, int *is_running, pthread_mutex_t mutex);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_take_forks(t_philo *philo, int left_fork, int right_fork);

//philosopher.c
void		*one_philo_thread(void *arg);
void		one_philo(t_data *data);


//time.c
long long	get_time(void);
long long	get_time_since(long long start_time);

//utils.c
int			ft_strlen(char *str);
void		ft_putstr_fd(char *str, int i);
int			ft_atoi(char *str);
int			ft_usleep(size_t milliseconds);

#endif