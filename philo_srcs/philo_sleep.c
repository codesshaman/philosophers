/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:22:49 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:12:59 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_time(struct timeval *tp_before)
{
	int				time_dif;
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
		return (-1);
	time_dif = ((int)(tp.tv_sec - tp_before->tv_sec)) * 1000;
	time_dif += ((int)(tp.tv_usec - (int)tp_before->tv_usec)) / 1000;
	return (time_dif);
}

int	ft_sleep(t_vars *vars, unsigned int time_to_sleep)
{
	long long	i;
	long long	j;

	i = ft_get_time(&vars->tp);
	if (i < 0)
		return (1);
	i += time_to_sleep;
	j = ft_get_time(&vars->tp);
	if (j < 0)
		return (1);
	while (j < i)
	{
		usleep(100);
		j = ft_get_time(&vars->tp);
		if (j < 0)
			return (1);
	}
	return (0);
}
