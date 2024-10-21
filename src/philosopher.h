/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:16 by alexis            #+#    #+#             */
/*   Updated: 2024/10/16 15:39:53 by alexis           ###   ########.fr       */
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
	int				nbr_must_eat;
	pthread_mutex_t	is_running_mutex;
	pthread_mutex_t	*forks;
}					t_data;

// main.c

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
void	setup_arg(t_data *data, char **argv);

#endif