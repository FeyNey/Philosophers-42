/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:32 by alexis            #+#    #+#             */
/*   Updated: 2024/10/21 19:40:40 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	display_data(t_data *data)
{
	printf("nb_of_philo : %i\n", data->nb_of_philo);
	printf("time_to_die : %i\n", data->time_to_die);
	printf("time_to_eat : %i\n", data->time_to_eat);
	printf("time_to_sleep : %i\n", data->time_to_sleep);
	printf("time_must_eat : %i\n", data->time_must_eat);
	printf("start time of the simulation : %lli\n", data->start_time);
}
