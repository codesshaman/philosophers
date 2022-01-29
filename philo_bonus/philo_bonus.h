/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:38:33 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:37:47 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include "philo_bonus.h"

typedef struct s_philo
{
	pthread_t	tid;
	sem_t		*actions;
	size_t		philo_ind;
	size_t		total_nbr_of_eating;
	time_t		time_of_last_eating;
	int			nbr_of_eating;
}				t_philo;

// Конфиг с семафорами и параметрами времени

typedef struct s_arg
{
	pthread_t	tid;
	pid_t		*pid_philo;
	sem_t		*write_sem;
	sem_t		*fork_sem;
	sem_t		*stop;
	sem_t		*eat_enough;
	int			nbr_philo;
	time_t		start_time;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	size_t		nbr_of_eating;

	t_philo		philo;

}				t_arg;

void	ft_taking_forks_eating(t_arg *args);
void	ft_sleeping_thinking(t_arg *args);
void	*philo_cycle(void *args);
void	*ft_eating_checker(void *arg);
void	*ft_death_checker(void *arg);
int		ft_init_args(t_arg *args, int argc, char **argv);
void	ft_init_philo(t_arg *args);
long	ft_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);

#endif
