/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:21:07 by alexis            #+#    #+#             */
/*   Updated: 2024/10/16 15:03:39 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
	t_data	*data;
	// int	return_value;

	// return_value = 0;
	if (check_errors(argc, argv + 1))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	setup_arg(data, argv);
	// display_data(data);
	if (data->nb_of_philo == 0)
		return (free(data), 0);
	init_mutex(data);
	if (data->nb_of_philo == 1)
		one_philo(data);
	else
		multiple_philo(data);
	destroy_mutexes(data);
	return (free(data), 0);
}
