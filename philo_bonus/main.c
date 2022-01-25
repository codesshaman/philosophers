/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:37:34 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:37:47 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_create_procs(t_phil *phil)
{
	unsigned int	i;
	t_phil			*phil_step;

	i = -1;
	phil_step = phil;
	while (++i < phil_step->vars->num_of_philos)
	{
		phil_step->pid = fork();
		if (phil_step->pid < 0)
			exit(ft_error("Fork error.\n"));
		if (phil_step->pid == 0)
			ft_child(phil_step);
		phil_step = phil_step->next;
	}
}

int	ft_wait_procs(t_phil *phil)
{
	unsigned int	i;
	unsigned int	count_eater_phil;
	int				*status;

	count_eater_phil = 0;
	i = -1;
	while (++i < phil->vars->num_of_philos)
	{
		if (waitpid(-1, status, 0) < 0)
			ft_error("Error waitpid.\n");
		if (WSTOPSIG(status) == 1)
			count_eater_phil++;
		if (count_eater_phil == phil->vars->num_of_philos || \
			WSTOPSIG(status) == 2)
			exit(0);
		else if (WSTOPSIG(status) > 2)
			return (1);
		phil = phil->next;
	}
	return (0);
}

int	ft_do(t_vars *vars, t_phil **phil)
{
	*phil = NULL;
	if (ft_init_phils(vars, phil))
		return (ft_error("ERROR : Malloc.\n"));
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	vars->semfork = sem_open(SEM_FORK, O_CREAT, 0660, vars->num_of_philos);
	vars->semwrite = sem_open(SEM_WRITE, O_CREAT, 0660, 1);
	if (vars->semfork == SEM_FAILED || vars->semwrite == SEM_FAILED)
		return (ft_error("Error. Can not create semafore.\n"));
	if (gettimeofday(&vars->tp, NULL))
		return (ft_error("Error gettimeofday\n"));
	ft_create_procs(*phil);
	ft_wait_procs(*phil);
	sem_close(vars->semfork);
	sem_close(vars->semwrite);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_phil	*phil;

	if (argc < 5 || argc > 6)
		return (ft_error("Error. Wrong number arguments.\n"));
	if (ft_init_vars(&vars, argc, argv))
		return (ft_error("Error. Wrong arguments.\n"));
	ft_do(&vars, &phil);
	phil->prev->next = NULL;
	ft_phil_lstclear(&phil, 0);
}
