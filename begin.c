/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:45:29 by jperales          #+#    #+#             */
/*   Updated: 2023/02/14 11:53:33 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_initial_values(t_general *var)
{
	int	i;

	i = 0;
	var->is_dead = 0;
	var->all_eaten = 0;
	pthread_mutex_init(&var->eating, NULL);
	pthread_mutex_init(&var->write, NULL);
	pthread_mutex_init(&var->death, NULL);
	while (i < var->nb_philos)
	{
		pthread_mutex_init(&var->forks[i], NULL);
		var->philosophers[i].nb = i + 1;
		var->philosophers[i].ate = 0;
		var->philosophers[i].last_ate = 0;
		var->philosophers[i].var = var;
		var->philosophers[i].right_fork = i;
		if (i == 0)
			var->philosophers[i].left_fork = var->nb_philos - 1;
		else
			var->philosophers[i].left_fork = i - 1;
		i++;
	}
}

void	ft_print_initial(t_general *var)
{
	printf("\nNumber of Philosophers:\t%3d\n", var->nb_philos);
	printf("Time to die:\t\t%3ld\n", var->time_die);
	printf("Time to eat:\t\t%3ld\n", var->time_ate);
	printf("Time to sleep:\t\t%3ld\n", var->time_sleep);
	if (var->nb_ates > 0)
		printf("Nº of ates each Philo:\t%3d\n", var->nb_ates);
	printf("\n\n");
	printf("TIME(ms)\tPHILO Id\tMESSAGE\n\n");
}
