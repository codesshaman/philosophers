/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:42:27 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:42:28 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_check_status(const int *status)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (status[i] < 0)
			return (1);
	return (0);
}

int	ft_init_vars(t_vars *vars, int argc, char **argv)
{
	int	status[5];

	vars->num_of_philos = ft_atoi(argv[1], &status[0]);
	vars->time_to_die = ft_atoi(argv[2], &status[1]);
	vars->time_to_eat = ft_atoi(argv[3], &status[2]);
	vars->time_to_sleep = ft_atoi(argv[4], &status[3]);
	if (argc > 5)
		vars->num_time_to_eat = ft_atoi(argv[5], &status[4]);
	else
	{
		vars->num_time_to_eat = -1;
		status[4] = 0;
	}
	if (ft_check_status(status) || vars->time_to_sleep > MAX || \
			vars->time_to_die > MAX || vars->time_to_eat > MAX || \
				vars->num_of_philos == 0 || \
						!vars->num_time_to_eat)
		return (1);
	return (0);
}

int	ft_init_phils(t_vars *vars, t_phil **phil)
{
	unsigned int	i;

	i = -1;
	while (++i < vars->num_of_philos)
		if (ft_phil_add_back(phil, i, vars))
			return (ft_phil_lstclear(phil, 1));
	(*phil)->prev = ft_phil_last(phil);
	(*phil)->prev->next = *phil;
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
