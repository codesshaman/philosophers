/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:02:40 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:02:45 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Инициализация философов

void	ft_init_philosophers(t_arg *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->nbr_philo);
	while (i < args->nbr_philo)
	{
		philos[i].philo_id = i;
		philos[i].nbr_philo = args->nbr_philo;
		philos[i].total_nbr_of_eating = 0;
		philos[i].total_nbr_of_eating_1 = args->nbr_of_eating;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].time_to_die = args->time_to_die;
		philos[i].time_of_last_eating = ft_time();
		philos[i].limit_of_life = args->time_to_die;
		philos[i].stop = 0;
		philos[i].l_f = \
			&args->forks[philos[i].philo_id];
		philos[i].r_f = \
			&args->forks[(philos[i].philo_id + 1) % args->nbr_philo];
		philos[i].arg = args;
		i++;
	}
	args->all_philos = philos;
}

// Инициализируем взаимные исключения

void	ft_init_mutex(t_arg *args)
{
	int				nbr_ph;
	pthread_mutex_t	*mutex;

	nbr_ph = args->nbr_philo;
	mutex = malloc(sizeof(pthread_mutex_t) * nbr_ph);
	while (nbr_ph--)
		pthread_mutex_init(&mutex[nbr_ph], NULL);
	pthread_mutex_init(&args->lock_print, NULL);
	args->forks = mutex;
}

// Инициализируем потоки

void	ft_init_threads(t_arg *args)
{
	int			nbr_ph;
	pthread_t	*threads;
	pthread_t	s_tid;

	nbr_ph = args->nbr_philo;
	threads = malloc(sizeof(pthread_t) * nbr_ph);
	while (nbr_ph--)
		pthread_create(&threads[nbr_ph], \
			NULL, ft_process, (void *)&args->all_philos[nbr_ph]);
	pthread_create(&s_tid, NULL, ft_monitor, (void *)args->all_philos);
	pthread_join(s_tid, NULL);
	args->tids = threads;
}

// Завершаем потоки, разблокируем исключения

void	ft_end_threads(t_arg *args)
{
	int	nbr_ph;

	nbr_ph = args->nbr_philo;
	if (nbr_ph == 1)
	{
		pthread_mutex_unlock(&args->forks[0]);
	}
	while (nbr_ph)
	{
		nbr_ph--;
		pthread_join(args->tids[nbr_ph], NULL);
	}
}

// Заполняем структуру аргументами

int	ft_init_args(t_arg *args, int argc, char **argv)
{
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->dead = 0;
	if (argc == 6)
		args->nbr_of_eating = ft_atoi(argv[5]);
	if (argc == 5)
	{
		if (args->nbr_philo < 1)
			return (0);
		args->nbr_of_eating = -1;
	}
	if (argc == 6)
	{
		if (args->nbr_of_eating < 1)
			return (0);
	}
	return (0);
}
