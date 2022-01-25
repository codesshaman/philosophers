

#include "philo_bonus.h"

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
