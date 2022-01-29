/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:42:15 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:42:17 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_init_tid(t_arg *args)
{
	if (args->nbr_of_eating)
	{
		if (pthread_create(&args->tid, NULL, &ft_eating_checker, args))
		{
			printf("Error pthread");
			return (1);
		}
		pthread_detach(args->tid);
	}
	return (0);
}

void	ft_init_philo(t_arg *args)
{
	args->philo.time_of_last_eating = ft_time();
	if (pthread_create(&args->tid, NULL, &ft_death_checker, args))
	{
		printf("Error pthread");
		sem_post(args->stop);
	}
	pthread_detach(args->tid);
}

// Удаляем существующие семафоры через sem_unlink,
// А затем открываем их по новой и заносим в структуру.

static int	ft_init_sempahore(t_arg *args)
{
	sem_unlink("fork_sem");
	sem_unlink("write_sem");
	sem_unlink("stop");
	sem_unlink("eat_enough");
	args->fork_sem = sem_open("fork_sem", O_CREAT | \
		O_EXCL, S_IRWXU, args->nbr_philo);
	args->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	args->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (args->nbr_of_eating)
		args->eat_enough = sem_open("eat_enough", O_CREAT | O_EXCL, S_IRWXU, 0);
	return (0);
}

// Обнуляем структуру, затем заполняем её значениями из argv

int	ft_init_args(t_arg *args, int argc, char **argv)
{
	memset(args, 0, sizeof(t_arg));
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nbr_of_eating = ft_atoi(argv[5]);
	args->pid_philo = malloc(sizeof(pid_t) * args->nbr_philo);
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
	memset(args->pid_philo, 0, sizeof(pid_t) * args->nbr_philo);
	ft_init_sempahore(args);
	ft_init_tid(args);
	return (0);
}
