/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:41:28 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:41:31 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Ждём или берём свободную вилку

void	ft_taking_forks_eating(t_arg *args)
{
	sem_wait(args->fork_sem);
	sem_wait(args->fork_sem);
	sem_wait(args->write_sem);
	printf("%ld %lu has taken a fork\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	printf("%ld %lu has taken a fork\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	sem_wait(args->write_sem);
	printf("%ld %lu is eating\n", ft_time() - args->start_time, \
		args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	args->philo.time_of_last_eating = ft_time();
	args->philo.total_nbr_of_eating += 1;
	if (args->philo.total_nbr_of_eating == args->nbr_of_eating)
		sem_post(args->eat_enough);
	ft_usleep(args->time_to_eat);
	sem_post(args->fork_sem);
	sem_post(args->fork_sem);
}

// Спим или мыслим

void	ft_sleeping_thinking(t_arg *args)
{
	sem_wait(args->write_sem);
	printf("%ld %lu is sleeping\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
	ft_usleep(args->time_to_sleep);
	sem_wait(args->write_sem);
	printf("%ld %lu is thinking\n", \
		ft_time() - args->start_time, args->philo.philo_ind + 1);
	sem_post(args->write_sem);
}

// Зацикливаем действия философа

void	*philo_cycle(void *args)
{
	t_arg	*philo;

	philo = (t_arg *)args;
	philo->start_time = ft_time();
	while (1)
	{
		ft_taking_forks_eating(philo);
		ft_sleeping_thinking(philo);
	}
	return (NULL);
}

// Проверяем, есть ли возможность пожрать

void	*ft_eating_checker(void *arg)
{
	t_arg	*args;
	int		i;

	args = arg;
	i = -1;
	sem_wait(args->write_sem);
	while (++i < args->nbr_philo)
	{
		sem_post(args->write_sem);
		sem_wait(args->eat_enough);
		sem_wait(args->write_sem);
	}
	sem_post(args->stop);
	return (NULL);
}

// Проверяем, не пора ли умереть...

void	*ft_death_checker(void *arg)
{
	t_arg	*args;
	long	time_now;

	args = arg;
	while (1)
	{
		time_now = ft_time();
		if (time_now - args->philo.time_of_last_eating > args->time_to_die)
		{
			sem_wait(args->write_sem);
			printf("%ld %lu died\n", \
				ft_time() - args->start_time, args->philo.philo_ind + 1);
			sem_post(args->stop);
			exit(0);
		}
	}
	return (NULL);
}
