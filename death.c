/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:32:55 by jperales          #+#    #+#             */
/*   Updated: 2022/10/26 16:47:39 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo *ph)
{
	int	i;

	i = 0;
	while (!(ph->var->all_eaten))
	{
		while (i < ph->var->nb_philos && !(ph->var->is_dead))
		{
			pthread_mutex_lock(&ph->var->eating);
			if ((ft_get_time() - ph->last_ate) > ph->var->time_die)
			{
//				ft_print_msg(ph, "Is DEAD");
//				printf("%ld\t\tPhilo %d \tIs DEAD\n", (ft_get_time() - ph->var->time_start), ph->nb);
				ph->var->is_dead = 1;
				ft_print_msg(ph, "Is DEAD");
				break ;
			}
			pthread_mutex_unlock(&ph->var->eating);
			usleep(50);
			i++;
		}
		if (ph->var->is_dead)
			break ;
		i = 0;
		pthread_mutex_lock(&ph->var->eating);
		while (ph->var->nb_ates != 0 && i < ph->var->nb_philos && ph[i].ate >= ph->var->nb_ates)
			i++;
		if (i == ph->var->nb_philos)
			ph->var->all_eaten = 1;
		usleep(50);
		pthread_mutex_unlock(&ph->var->eating);
	}
}
