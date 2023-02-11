/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:27:01 by jperales          #+#    #+#             */
/*   Updated: 2022/10/26 20:13:27 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_eaten(t_philo *ph)
{
	int	i;

	i = 0;
	while (ph->var->nb_ates != 0 && i < ph->var->nb_philos && (ph[i].ate >= ph->var->nb_ates))
		i++;
	if (i == ph->var->nb_philos)
		ph->var->all_eaten = 1;
	usleep(200);
}

void	ft_check_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->var->death);
	if ((ft_get_time() - ph->last_ate) > ph->var->time_die
		&& ph->var->is_dead == 0)
	{
		ph->var->is_dead = 1;
		printf("%ld\t\tPhilo %d \tIs DEAD!\n",
			(ft_get_time() - ph->var->time_start), ph->nb);
	}
	pthread_mutex_unlock(&ph->var->death);
}

void	ft_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->var->forks[ph->left_fork]);
	ft_print_msg(ph, "Has taken a l_Fork");
	ft_check_death(ph);
	pthread_mutex_lock(&ph->var->forks[ph->right_fork]);
	ft_print_msg(ph, "Has taken a r_Fork");
	ft_check_death(ph);
	ft_print_msg(ph, "Is eating");
	ph->last_ate = ft_get_time();
	ph->ate++;
	pthread_mutex_lock(&ph->var->eating);
	ft_check_eaten(ph);
	pthread_mutex_unlock(&ph->var->eating);
	ft_time_pass(ph->var, ph->var->time_ate);
	ft_check_death(ph);
	pthread_mutex_unlock(&ph->var->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->var->forks[ph->right_fork]);
	ft_check_death(ph);
	ft_print_msg(ph, "Is sleeping");
	ft_time_pass(ph->var, ph->var->time_sleep);
	ft_check_death(ph);
	ft_print_msg(ph, "Is thinking");
}

/*void	ft_sleep(t_philo *ph)
{	
	if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
		return ;
	ft_print_msg(ph, "Is sleeping");
	if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
		return ;
	ft_time_pass(ph->var, ph->var->time_sleep);
}

void	ft_think(t_philo *ph)
{
	if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
		return ;
	ft_print_msg(ph, "Is thinking");
	if (ph->var->all_eaten == 1 || ph->var->is_dead == 1)
		return ;
}*/
