/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:02:20 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 15:30:18 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Создаём потоки

static int	ft_pthread_cicle(t_phil **phil)
{
	t_phil			*phil_step;
	unsigned int	i;

	phil_step = *phil;
	if (gettimeofday(&phil_step->vars->tp, NULL))
		return (ft_error("Error gettimeofday\n"));
	i = 0;
	while (i < phil_step->vars->num_of_philos)
	{
		if (pthread_create(&phil_step->thread, NULL, &ft_func, phil_step))
			return (ft_error("Can not create thread.\n"));
		if (pthread_detach(phil_step->thread))
			return (ft_error("Can not detach thread.\n"));
		phil_step = phil_step->next;
		i++;
	}
	return (0);
}

// Убиваем потоки

static int	ft_destr_mutex(t_phil *phil)
{
	t_phil			*phil_step;
	unsigned int	i;

	i = -1;
	phil_step = phil;
	while (++i < phil->vars->num_of_philos)
	{
		if (pthread_mutex_destroy(&phil_step->mutex))
		{
			pthread_mutex_unlock(&phil_step->mutex);
			pthread_mutex_destroy(&phil_step->mutex);
		}
		phil_step = phil_step->next;
	}
	if (pthread_mutex_destroy(&phil_step->vars->mutex_out))
	{
		pthread_mutex_unlock(&phil_step->vars->mutex_out);
		pthread_mutex_destroy(&phil_step->vars->mutex_out);
	}
	return (1);
}

// Действия философа

int	ft_do(t_vars *vars, t_phil **phil)
{
	t_phil	*phil_step;
	int		i;

	*phil = NULL;
	if (ft_init_phils(vars, phil))
		return (ft_error("ERROR : Malloc.\n"));
	if (ft_pthread_cicle(phil))
		return (1);
	phil_step = *phil;
	while (phil_step)
	{
		i = ft_check_dead(phil_step);
		if (i > 0)
			return (ft_destr_mutex(phil_step));
		else if (i < 0)
		{
			ft_destr_mutex(phil_step);
			return (ft_error("Error gettimeofday\n"));
		}
		phil_step = phil_step->next;
	}
	return (0);
}

// Основное тело программы

int	main(int argc, char **argv)
{
	t_vars	*vars;
	t_phil	*phil;

	if (argc < 5 || argc > 6)
		return (ft_error("Error. Wrong number arguments.\n"));
	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);
	if (ft_init_vars(vars, argc, argv))
		return (ft_error("Error. Wrong arguments.\n"));
	ft_do(vars, &phil);
	phil->prev->next = NULL;
	ft_phil_lstclear(&phil, 0);
	free(vars);
}
