

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include  <pthread.h>
# define MAX 4294967

typedef struct s_vars
{
	struct timeval		tp;
	unsigned int		num_of_philos;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	long long			num_time_to_eat;
	int					dead;
	int					end;
	pthread_mutex_t		mutex_out;
}	t_vars;
typedef struct s_phil
{
	unsigned int	number;
	unsigned int	time_last_eat;
	int				count_dinner;
	t_vars			*vars;
	struct s_phil	*next;
	struct s_phil	*prev;
	pthread_mutex_t	mutex;
	pthread_t		thread;
}	t_phil;
t_phil			*ft_phil_last(t_phil **phil);
unsigned int	ft_atoi(const char *str, int *i);
void			*ft_func(void *arg);
int				ft_mutex_lock(t_phil *phil);
void			ft_mutex_unclock(t_phil *phil);
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
#endif