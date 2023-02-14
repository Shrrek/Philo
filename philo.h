/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperales <jperales@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:31:38 by jperales          #+#    #+#             */
/*   Updated: 2023/02/14 12:57:24 by jperales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int					nb;
	int					ate;
	long				last_ate;
	pthread_t			pthread;
	int					left_fork;
	int					right_fork;
	struct s_general	*var;
}	t_philo;

typedef struct s_general
{
	int				nb_philos;
	long			time_die;
	long			time_ate;
	long			time_sleep;
	int				nb_ates;
	long			time_start;
	pthread_mutex_t	philo_mutex;
	t_philo			philosophers[200];
	int				is_dead;
	int				all_eaten;
	pthread_mutex_t	eating;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	write;
	pthread_mutex_t	death;
}	t_general;

int		ft_atoi(char	*str);
long	ft_get_time(void);
void	ft_create_pthreads(t_general *var);
void	ft_initial_values(t_general *var);
void	ft_run(t_general *var);
void	*ft_routine(void *arg);
void	ft_eat(t_philo *ph);
void	ft_sleep(t_philo *ph);
void	ft_think(t_philo *ph);
void	ft_time_pass(t_general *var, long time);
void	ft_print_msg(t_philo *ph, char *msg);
void	ft_death(t_philo *ph);
void	ft_check_death(t_philo *ph);
void	ft_check_eaten(t_philo *ph);
void	ft_destroy(t_general *var);
void	ft_errors1(int argc, char **argv);
void	ft_errors2(char **argv);

#endif
