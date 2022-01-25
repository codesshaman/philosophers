
#include "philo_bonus.h"

int	ft_check_dead(t_phil *phil)
{
	long long	var;

	var = ft_get_time(&phil->vars->tp);
	if (var < 0)
		return (-1);
	if (var >= phil->time_last_eat + phil->vars->time_to_die)
	{
		if ((phil->vars->num_time_to_eat > 0 && \
			phil->count_dinner < phil->vars->num_time_to_eat) || \
				phil->vars->num_time_to_eat < 0)
		{
			phil->dead = 1;
			if (ft_write(phil, 'd'))
				return (-1);
		}
	}
	return (0);
}
