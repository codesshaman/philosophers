/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseastar <mseastar@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:02:22 by mseastar          #+#    #+#             */
/*   Updated: 2022/01/16 16:57:55 by mseastar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <semaphore.h>
# define MAX 4294967
# define SEM_FORK "/mysemnamefork"
# define SEM_WRITE "/mysemnamewrite"

typedef struct s_vars
{
	struct timeval		tp;
	unsigned int		num_of_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	long long			num_time_to_eat;
	sem_t				*semfork;
	sem_t				*semwrite;
}	t_vars;
typedef struct s_phil
{
	unsigned int	number;
	unsigned int	time_last_eat;
	int				count_dinner;
	int				status;
	int				dead;
	t_vars			*vars;
	struct s_phil	*next;
	struct s_phil	*prev;
	pid_t			pid;
}	t_phil;
t_phil			*ft_phil_last(t_phil **phil);
unsigned int	ft_atoi(const char *str, int *i);
int				ft_error(char *str);
int				ft_get_time(struct timeval *tp_before);
int				ft_init_vars(t_vars *vars, int argc, char **argv);
int				ft_phil_add_back(t_phil **phil, unsigned int num_philo, \
t_vars *vars);
int				ft_phil_lstclear(t_phil **phil, int status);
int				ft_init_phils(t_vars *vars, t_phil **phil);
int				ft_write(t_phil *phil, char c);
int				ft_check_dead(t_phil *phil);
int				ft_do(t_vars *vars, t_phil **phil);
int				ft_sleep(t_vars *vars, unsigned int time_to_sleep);
void			ft_child(t_phil *phil);
int				ft_semfork_lock(t_phil *phil);
void			ft_semfork_unlock(t_phil *phil);
#endif