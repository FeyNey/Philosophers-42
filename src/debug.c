/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:32 by alexis            #+#    #+#             */
/*   Updated: 2024/10/16 15:32:39 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_data(t_data *data)
{
	printf("nb_of_philo : %i\n", data->nb_of_philo);
	printf("time_to_die : %i\n", data->time_to_die);
	printf("time_to_eat : %i\n", data->time_to_eat);
	printf("time_to_sleep : %i\n", data->time_to_sleep);
	printf("nbr_must_eat : %i\n", data->nbr_must_eat);
}
