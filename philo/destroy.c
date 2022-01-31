/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:02:09 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/31 22:38:04 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Освобождаем память всех потоков

void	free_all(t_arg *args)
{
	free(args->tids);
	free(args->all_philos);
	free(args->forks);
}

// Разблокируем и разрушаем исключения

void	unlock_and_destroy_mutex(t_arg *args)
{
	int	nbr_ph;

	nbr_ph = args->nbr_philo;
	while (nbr_ph--)
	{
		pthread_mutex_unlock(&args->forks[nbr_ph]);
		pthread_mutex_destroy(&args->forks[nbr_ph]);
	}
	pthread_mutex_unlock(&(*args).lock_print);
	pthread_mutex_destroy(&(*args).lock_print);
}

// Выводим сообщение о несоответствии аргументов

void	ft_check_args(void)
{
	printf("Your need enter 4 or 5 arguments:\n");
	printf("\n");
	printf("1: Number of philosophers\n");
	printf("2: Time to die\n");
	printf("3: Time to eat\n");
	printf("4: Time to sleep\n");
	printf("5: Number of eatings\n");
}

// Выводим сообщение о несоответствии аргументов

void	break_program(void)
{
	printf("Number is not correct\n");
	exit(1);
}
