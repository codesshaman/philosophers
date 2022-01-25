
#include "philo_bonus.h"

int	ft_get_time(struct timeval *tp_before)
{
	int				time_dif;
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
		return (-1);
	time_dif = ((int)(tp.tv_sec - tp_before->tv_sec)) * 1000;
	time_dif += ((int)(tp.tv_usec - (int)tp_before->tv_usec)) / 1000;
	return (time_dif);
}
