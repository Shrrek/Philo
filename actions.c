/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:27:01 by jperales          #+#    #+#             */
/*   Updated: 2023/02/14 13:09:15 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_eaten(t_philo *ph)
{
	int	i;

	i = 0;
	while (ph->var->nb_ates != 0 && i < ph->var->nb_philos
		&& (ph[i].ate >= ph->var->nb_ates))
		i++;
	if (i == ph->var->nb_philos)
		ph->var->is_dead = 1;
	usleep(200);
}

void	ft_check_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->var->death);
	if ((ft_get_time() - ph->last_ate) > ph->var->time_die
		&& ph->var->is_dead == 0)
	{
		ft_print_msg(ph, "died");
		ph->var->is_dead = 1;
	}
	pthread_mutex_unlock(&ph->var->death);
}

void	ft_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->var->forks[ph->left_fork]);
	ft_print_msg(ph, "has taken a fork");
	pthread_mutex_lock(&ph->var->forks[ph->right_fork]);
	ft_print_msg(ph, "has taken a fork");
	ft_print_msg(ph, "is eating");
	ph->last_ate = ft_get_time();
	ph->ate++;
	pthread_mutex_lock(&ph->var->eating);
	ft_check_eaten(ph);
	pthread_mutex_unlock(&ph->var->eating);
	ft_time_pass(ph->var, ph->var->time_ate);
	pthread_mutex_unlock(&ph->var->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->var->forks[ph->right_fork]);
	ft_print_msg(ph, "is sleeping");
	ft_time_pass(ph->var, ph->var->time_sleep);
	ft_check_death(ph);
	ft_print_msg(ph, "is thinking");
}
