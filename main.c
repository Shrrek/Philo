/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:01:08 by jperales          #+#    #+#             */
/*   Updated: 2023/02/14 13:06:49 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_general	var;

	ft_errors1(argc, argv);
	ft_errors2(argv);
	var.nb_philos = ft_atoi(argv[1]);
	var.time_die = ft_atoi(argv[2]);
	var.time_ate = ft_atoi(argv[3]);
	var.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		var.nb_ates = ft_atoi(argv[5]);
	else
		var.nb_ates = 0;
	ft_initial_values(&var);
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
		pthread_create(&ph[i].pthread, NULL, ft_routine, &(ph[i]));
		ph[i].last_ate = ft_get_time();
		i++;
	}
	ft_destroy(var);
}

void	ft_destroy(t_general *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philos)
	{
		pthread_join(var->philosophers[i].pthread, NULL);
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
	pthread_mutex_destroy(&var->death);
}

void	*ft_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *) arg;
	if (ph->var->nb_philos == 1)
	{
		ft_print_msg(ph, "has taken a fork");
		ft_time_pass(ph->var, ph->var->time_die);
		ft_print_msg(ph, "died");
		pthread_mutex_unlock(&ph->var->forks[ph->left_fork]);
		return (NULL);
	}
	if (ph->nb % 2 == 0)
		usleep(1000);
	while (!ph->var->is_dead && !ph->var->all_eaten)
	{
		ft_check_death(ph);
		ft_check_eaten(ph);
		if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
			break ;
		ft_eat(ph);
		if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
			break ;
		ft_check_death(ph);
	}
	return (NULL);
}
