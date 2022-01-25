/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:42:02 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:42:04 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_write(t_phil *phil, char c)
{
	long long	i;

	i = ft_get_time(&phil->vars->tp);
	if (i < 0)
		return (1);
	if ((phil->dead && c != 'd'))
		exit(2);
	sem_wait(phil->vars->semwrite);
	if (c == 'e')
		printf("%lld %u is eating\n", i, phil->number);
	else if (c == 'f')
		printf("%lld %u has taken a fork\n", i, phil->number);
	else if (c == 's')
		printf("%lld %u is sleeping\n", i, phil->number);
	else if (c == 't')
		printf("%lld %u is thinking\n", i, phil->number);
	else if (c == 'd')
	{
		printf("%lld %u died\n", i, phil->number);
		kill(phil->pid, SIGKILL);
		exit(2);
	}
	sem_post(phil->vars->semwrite);
	return (0);
}

int	ft_semfork_lock(t_phil *phil)
{
	sem_wait(phil->vars->semfork);
	if (ft_write(phil, 'f'))
		return (1);
	sem_wait(phil->vars->semfork);
	if (ft_write(phil, 'f'))
		return (1);
	return (0);
}

void	ft_semfork_unlock(t_phil *phil)
{
	sem_post(phil->vars->semfork);
	sem_post(phil->vars->semfork);
}
