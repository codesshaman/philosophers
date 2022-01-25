
#include "philo_bonus.h"

int	ft_sleep(t_vars *vars, unsigned int time_to_sleep)
{
	long long	i;
	long long	j;

	i = ft_get_time(&vars->tp);
	if (i < 0)
		return (1);
	i += time_to_sleep;
	j = ft_get_time(&vars->tp);
	if (j < 0)
		return (1);
	while (j < i)
	{
		usleep(100);
		j = ft_get_time(&vars->tp);
		if (j < 0)
			return (1);
	}
	return (0);
}
