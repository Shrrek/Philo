/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:01:08 by jperales          #+#    #+#             */
/*   Updated: 2022/10/26 18:10:14 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_general	var;
	int			i;
	int			j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
	{
		write(1, "Error. Invalid number of arguments.\n", 36);
		return (1);
	}
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write (1, "Error. Arguments must be numbers.\n", 34);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	if ((ft_atoi(argv[1])) > 200)
	{
		write (1, "Error. Number of Philosophers must be less than 200\n", 52);
		return (1);
	}
	if ((ft_atoi(argv[1])) == 0 || (ft_atoi(argv[2])) == 0
		|| (ft_atoi(argv[3])) == 0 || (ft_atoi(argv[4])) == 0)
	{
		write (1, "Error. Invalid arguments.\n", 26);
		return (1);
	}
	var.nb_philos = ft_atoi(argv[1]);
	var.time_die = ft_atoi(argv[2]);
	var.time_ate = ft_atoi(argv[3]);
	var.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var.nb_ates = ft_atoi(argv[5]);
	else
		var.nb_ates = 0;
	ft_initial_values(&var);
	ft_print_initial(&var);
	ft_run(&var);
	return (0);
}

void	ft_run(t_general *var)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = var->philosophers;
	var->time_start = ft_get_time();
	while (i < var->nb_philos)
	{
		ph[i].last_ate = ft_get_time();
		pthread_create(&ph[i].pthread, NULL, ft_routine, &(ph[i]));
		pthread_mutex_lock(&var->eating);
		pthread_mutex_unlock(&var->eating);
		i++;
	}
	i = 0;
	while (i < var->nb_philos)
	{
		pthread_join(ph[i].pthread, NULL);
		i++;
	}
	i = 0;
	while (i < var->nb_philos)
	{
		pthread_mutex_destroy(&var->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&var->eating);
	pthread_mutex_destroy(&var->write);
}

void	*ft_routine(void *arg)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *) arg;
	if (ph->nb % 2 == 0)
		usleep(1000);
	i = 0;
	while (!ph->var->is_dead && !ph->var->all_eaten)
	{
		if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
			break ;
		ft_eat(ph);
		if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
			break ;
		ft_sleep(ph);
		ft_think(ph);
		i++;
	}
	return (NULL);
}
