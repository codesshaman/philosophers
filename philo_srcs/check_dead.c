/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:22:26 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:13:27 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_eat(t_phil *phil)
{
	t_phil			*phil_step;
	unsigned int	i;

	phil_step = phil;
	i = -1;
	while (++i < phil->vars->num_of_philos)
	{
		if (phil_step->count_dinner < phil_step->vars->num_time_to_eat)
			return (1);
		phil_step = phil_step->next;
	}
	return (0);
}

int	ft_check_dead(t_phil *phil)
{
	unsigned int	var;

	var = ft_get_time(&phil->vars->tp);
	if (var < 0)
		return (-1);
	if (var >= phil->time_last_eat + phil->vars->time_to_die)
	{
		if ((phil->vars->num_time_to_eat > 0 && \
			phil->count_dinner < phil->vars->num_time_to_eat) || \
				phil->vars->num_time_to_eat < 0)
		{
			phil->vars->dead = 1;
			ft_write(phil, 'd');
			return (1);
		}
	}
	if (phil->vars->num_time_to_eat > 0 && !ft_is_eat(phil))
	{
		phil->vars->end = 1;
		return (1);
	}
	return (0);
}
