/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:33:38 by jperales          #+#    #+#             */
/*   Updated: 2023/02/14 12:56:38 by jperales         ###   ########.fr       */
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
		printf("%ld\t\t %d \t%s\n",
			ft_get_time() - ph->var->time_start, ph->nb, msg);
	pthread_mutex_unlock(&ph->var->write);
}

void	ft_errors1(int argc, char **argv)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
	{
		write(1, "Error. Invalid number of arguments.\n", 36);
		exit (0);
	}
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write (1, "Error. Arguments must be numbers.\n", 34);
				exit (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_errors2(char **argv)
{
	if ((ft_atoi(argv[1])) > 200)
	{
		write (1, "Error. Number of Philosophers must be less than 200\n", 52);
		exit (0);
	}
	if ((ft_atoi(argv[1])) == 0 || (ft_atoi(argv[2])) == 0
		|| (ft_atoi(argv[3])) == 0 || (ft_atoi(argv[4])) == 0)
	{
		write (1, "Error. Invalid arguments.\n", 26);
		exit (0);
	}
}
