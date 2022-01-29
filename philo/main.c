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

// Проверка аргументов на валидность

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
	ft_init_mutex(&args);
	ft_init_philosophers(&args);
	ft_init_threads(&args);
	ft_end_threads(&args);
	unlock_and_destroy_mutex(&args);
	free_all(&args);
	return (0);
}
