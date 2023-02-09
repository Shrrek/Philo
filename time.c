/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:58:14 by jperales          #+#    #+#             */
/*   Updated: 2022/10/18 17:07:09 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return ((1000 * time.tv_sec) + (time.tv_usec / 1000));
}

void	ft_time_pass(t_general *var, long time)
{
	long	finish;

	finish = ft_get_time() + time;
	while ((ft_get_time() < finish) && !(var->is_dead))
	{
		ft_check_death(var->philosophers);
		usleep(100);
	}
}
