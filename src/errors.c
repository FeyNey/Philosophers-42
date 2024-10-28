/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:52:19 by alexis            #+#    #+#             */
/*   Updated: 2024/10/25 17:29:03 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_not_digit(char *argv)
{
	int i;

	i = 0;
	if (argv[0] == '-' || argv[0] == '+')
		i++;
	while (argv[i])
	{
		if ((argv[i] < '0' || argv[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_errors(int argc, char **argv)
{
	int i;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo [number_of_philosophers] [time_to_die]\
 [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n\
		Last argument is obtional and is set by default to infinity.\n");
		return (1);
	}
	i = 0;
	while (i < (argc - 1))
	{
		if (is_not_digit(argv[i])) // only nbr except 'argv[i][0] who can also be '-' or '+'
		{
			ft_putstr_fd("Error : Arguments must all be numbers.\n", 2);
			return (1);
		}
		if (argv[i][0] == '-')
		{
			ft_putstr_fd("Error : Arguments must all be positives.\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
