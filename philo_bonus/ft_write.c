
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
