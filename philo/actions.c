/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:22:26 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:13:27 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Берём в руки вилку

void	taking_forks_else(t_philo *philo)
{
	pthread_mutex_lock(philo->l_f);
	pthread_mutex_lock(philo->r_f);
	pthread_mutex_lock(&philo->lock_print);
	if (philo->stop != 1)
	{
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->philo_id + 1);
		printf("%ld %d has taken a fork\n", \
			ft_time() - philo->start_time, philo->philo_id + 1);
	}
	pthread_mutex_unlock(&philo->lock_print);
}

// Берём вторую вилку

void	taking_forks(t_philo *philo)
{
	if ((philo->philo_id) % 2 == 0 && philo->philo_id + 1 != philo->nbr_philo)
	{
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(&philo->lock_print);
		if (philo->stop != 1)
		{
			printf("%ld %d has taken a fork\n", \
				ft_time() - philo->start_time, philo->philo_id + 1);
			printf("%ld %d has taken a fork\n", \
				ft_time() - philo->start_time, philo->philo_id + 1);
		}
		pthread_mutex_unlock(&philo->lock_print);
	}
	else
		taking_forks_else(philo);
}

// Питаемся

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is eating\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	philo->total_nbr_of_eating += 1;
	philo->time_of_last_eating = ft_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

// Засыпаем от переедания

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is sleeping\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
	ft_usleep(philo->time_to_sleep);
}

// Просыпаемся и мыслим, нафиг нам такая жизнь...

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_print);
	printf("%ld %d is thinking\n", \
		ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->lock_print);
}
