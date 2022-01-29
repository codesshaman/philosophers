/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:01:50 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:01:56 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	ft_cnt_of_eatings(t_philo *philo)
{
	int	flag_enough;
	int	i;

	if (philo->total_nbr_of_eating != -1 \
		&& philo->total_nbr_of_eating_1 > 0)
	{
		flag_enough = 1;
		i = -1;
		while (++i < philo->nbr_philo)
			if (philo[i].total_nbr_of_eating < philo->total_nbr_of_eating_1)
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while (i < philo[i].nbr_philo)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	died_philo(t_philo *philo, int i)
{
	philo->arg->dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d died\n", ft_time() - philo->start_time,
		philo[i].philo_id + 1);
	i = -1;
	while (i < philo[i].nbr_philo)
	{
		philo[i].stop = 1;
		i++;
	}
}

// 

void	*ft_monitor(void *args)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)args;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->nbr_philo)
		{
			time_now = ft_time();
			if (time_now - philo[i].time_of_last_eating > philo[i].limit_of_life)
			{
				died_philo(philo, i);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
		}
		if (ft_cnt_of_eatings(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}

// Обрабатываем философа после инициализации

void	*ft_process(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->time_of_last_eating = ft_time();
	philo->start_time = ft_time();
	while (!philo->arg->dead)
	{
		if (philo->arg->dead || philo->stop || ft_cnt_of_eatings(philo))
			return (NULL);
		taking_forks(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_eatings(philo))
			return (NULL);
		eating(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_eatings(philo))
			return (NULL);
		sleeping(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_eatings(philo))
			return (NULL);
		thinking(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_eatings(philo))
			return (NULL);
	}
	return (NULL);
}
