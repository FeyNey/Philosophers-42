/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:26:08 by acoste            #+#    #+#             */
/*   Updated: 2024/10/21 19:42:57 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long get_time_diff(long long start_time)
{
	struct	timeval	tn;
	long long		ts;

	gettimeofday(&tn, NULL);
	ts = tn.tv_sec * 1000 + tn.tv_usec / 1000;
	return (ts - start_time);
}
