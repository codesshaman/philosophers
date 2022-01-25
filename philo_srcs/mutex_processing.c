/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:01:50 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:01:56 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_write(t_phil *phil, char c)
{
	long long	i;

	i = ft_get_time(&phil->vars->tp);
	if (i < 0)
		return (1);
	if ((phil->vars->dead && c != 'd') || (phil->vars->end && c != 'e') || \
		phil->number == 0)
		return (0);
	pthread_mutex_lock(&phil->vars->mutex_out);
	if (c == 'e')
		printf("%lld %u is eating\n", i, phil->number);
	else if (c == 'f')
		printf("%lld %u has taken a fork\n", i, phil->number);
	else if (c == 's')
		printf("%lld %u is sleeping\n", i, phil->number);
	else if (c == 't')
		printf("%lld %u is thinking\n", i, phil->number);
	else if (c == 'd')
		printf("%lld %u died\n", i, phil->number);
	if ((!phil->vars->dead && !phil->vars->end) || \
		(phil->vars->dead && c != 'd'))
		pthread_mutex_unlock(&phil->vars->mutex_out);
	return (0);
}

void	*ft_func(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (!(phil->number % 2))
		usleep(1000);
	while (!phil->vars->dead && !phil->vars->end)
	{
		if (ft_mutex_lock(phil))
			return (NULL);
		phil->time_last_eat = ft_get_time(&phil->vars->tp);
		if (phil->time_last_eat < 0 || ft_write(phil, 'e') || \
		ft_sleep(phil->vars, phil->vars->time_to_eat))
			return (NULL);
		ft_mutex_unclock(phil);
		phil->count_dinner++;
		if (ft_write(phil, 's') || \
			ft_sleep(phil->vars, phil->vars->time_to_sleep) || \
			ft_write(phil, 't'))
			return (NULL);
	}
	return (NULL);
}

int	ft_mutex_lock(t_phil *phil)
{
	if (!phil->number % 2)
	{
		pthread_mutex_lock(&phil->mutex);
		if (ft_write(phil, 'f'))
			return (1);
		pthread_mutex_lock(&phil->prev->mutex);
	}
	else
	{
		pthread_mutex_lock(&phil->prev->mutex);
		ft_write(phil, 'f');
		pthread_mutex_lock(&phil->mutex);
	}
	if (ft_write(phil, 'f'))
		return (1);
	return (0);
}

void	ft_mutex_unclock(t_phil *phil)
{
	if (!phil->number % 2)
	{
		pthread_mutex_unlock(&phil->prev->mutex);
		pthread_mutex_unlock(&phil->mutex);
	}
	else
	{
		pthread_mutex_unlock(&phil->mutex);
		pthread_mutex_unlock(&phil->prev->mutex);
	}
}
