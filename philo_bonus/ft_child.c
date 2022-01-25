
#include "philo_bonus.h"

static void	*ft_func(void *arg)
{
	t_phil	*phil;
	int		i;

	phil = (t_phil *)arg;
	while (phil)
	{
		i = ft_check_dead(phil);
		if (i > 0)
			return (NULL);
		if (i < 0)
		{
			ft_error("Error gettimeofday.\n");
			return (NULL);
		}
	}
	return (NULL);
}

void	ft_child(t_phil *phil)
{
	pthread_t	thread;
	t_phil		*phil_thread;

	phil_thread = phil;
	pthread_create(&thread, NULL, &ft_func, phil_thread);
	pthread_detach(thread);
	while (!phil->dead)
	{
		if (ft_semfork_lock(phil) || ft_write(phil, 'e'))
			exit(3);
		phil->time_last_eat = ft_get_time(&phil->vars->tp);
		if (phil->time_last_eat < 0 || \
			ft_sleep(phil->vars, phil->vars->time_to_eat))
			exit(3);
		phil->count_dinner++;
		ft_semfork_unlock(phil);
		if (phil->vars->num_time_to_eat > 0 && \
			phil->count_dinner >= phil->vars->num_time_to_eat)
			exit(1);
		if (ft_write(phil, 's') || \
			ft_sleep(phil->vars, phil->vars->time_to_sleep) || \
				ft_write(phil, 't'))
			exit(3);
	}
	exit(0);
}
