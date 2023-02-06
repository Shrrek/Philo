/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:33:38 by jperales          #+#    #+#             */
/*   Updated: 2022/10/26 17:22:36 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	return (num);
}

void	ft_print_msg(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->var->write);
	if (!ph->var->is_dead)
		printf("%ld\t\tPhilo %d \t%s\n",
			ft_get_time() - ph->var->time_start, ph->nb, msg);
	pthread_mutex_unlock(&ph->var->write);
}
