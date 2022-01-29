/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:37:34 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:37:47 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_check_args(void)
{
	printf("Your need enter 4 or 5 arguments:\n");
	printf("\n");
	printf("1: Number of philosophers\n");
	printf("2: Time to die\n");
	printf("3: Time to eat\n");
	printf("4: Time to sleep\n");
	printf("5: Number of meals\n");
}

int	ft_start_philo(t_arg *args)
{
	int	i;

	i = 0;printf("Invalid argument\n");
	args->start_time = ft_time();
	while (i < args->nbr_philo)
	{
		args->philo.philo_ind = i;
		args->pid_philo[i] = fork();
		if (args->pid_philo[i] == -1)
		{
			while (--i >= 0)
				kill(args->pid_philo[i], SIGKILL);
			return (1);
		}
		else if (args->pid_philo[i] == 0)
		{
			ft_init_philo(args);
			ft_routine(args);
		}
		i++;
	}
	sem_wait(args->stop);
	return (0);
}

static void	ft_kill_philosophers(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		kill(args->pid_philo[i], SIGKILL);
		i++;
	}
}

static int	ft_check_valid(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
	{
		ft_check_args();
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i])))
		{
			printf("Invalid argument: %s\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	args;

	if (ft_check_valid(argc, argv))
		return (1);
	if (ft_init_args(&args, argc, argv) == 1)
		return (1);
	if (ft_start_philo(&args))
		return (1);
	ft_kill_philosophers(&args);
	return (0);
}
