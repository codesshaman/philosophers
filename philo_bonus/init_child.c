/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:42:15 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:42:17 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_dead(t_phil *phil)
{
	long long	var;

	var = ft_get_time(&phil->vars->tp);
	if (var < 0)
		return (-1);
	if (var >= phil->time_last_eat + phil->vars->time_to_die)
	{
		if ((phil->vars->num_time_to_eat > 0 && \
			phil->count_dinner < phil->vars->num_time_to_eat) || \
				phil->vars->num_time_to_eat < 0)
		{
			phil->dead = 1;
			if (ft_write(phil, 'd'))
				return (-1);
		}
	}
	return (0);
}

static void	*ft_func(void *arg)
{
	t_phil	*phil;
	int		i;

	phil = (t_phil *)arg;
	while (phil)
	{
		i = ft_check_dead(phil);
		if (i > 0)
			return (NULL);
		if (i < 0)
		{
			ft_error("Error gettimeofday.\n");
			return (NULL);
		}
	}
	return (NULL);
}

void	ft_child(t_phil *phil)
{
	pthread_t	thread;
	t_phil		*phil_thread;

	phil_thread = phil;
	pthread_create(&thread, NULL, &ft_func, phil_thread);
	pthread_detach(thread);
	while (!phil->dead)
	{
		if (ft_semfork_lock(phil) || ft_write(phil, 'e'))
			exit(3);
		phil->time_last_eat = ft_get_time(&phil->vars->tp);
		if (phil->time_last_eat < 0 || \
			ft_sleep(phil->vars, phil->vars->time_to_eat))
			exit(3);
		phil->count_dinner++;
		ft_semfork_unlock(phil);
		if (phil->vars->num_time_to_eat > 0 && \
			phil->count_dinner >= phil->vars->num_time_to_eat)
			exit(1);
		if (ft_write(phil, 's') || \
			ft_sleep(phil->vars, phil->vars->time_to_sleep) || \
				ft_write(phil, 't'))
			exit(3);
	}
	exit(0);
}
