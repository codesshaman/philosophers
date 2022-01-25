

#include "philo.h"

static t_phil	*ft_phil_new(t_phil **phil_lst, \
t_vars *vars, unsigned int num_philo)
{
	t_phil	*phil;

	phil = (t_phil *) malloc(sizeof (t_phil));
	if (phil == NULL || pthread_mutex_init(&phil->mutex, NULL))
		return (NULL);
	phil->number = num_philo + 1;
	phil->time_last_eat = 0;
	phil->count_dinner = 0;
	phil->vars = vars;
	phil->next = NULL;
	phil->prev = ft_phil_last(phil_lst);
	return (phil);
}

t_phil	*ft_phil_last(t_phil **phil)
{
	t_phil	*last;

	last = *phil;
	while (last && last->next)
		last = last->next;
	return (last);
}

int	ft_phil_lstclear(t_phil **phil, int status)
{
	t_phil	*phil_step;
	t_phil	*swap;

	phil_step = *phil;
	while (phil_step)
	{
		swap = (phil_step)->next;
		free(phil_step);
		phil_step = swap;
	}
	*phil = NULL;
	if (status)
		return (ft_error("List is not created.\n"));
	else
		return (0);
}

int	ft_phil_add_back(t_phil **phil, unsigned int num_philo, t_vars *vars)
{
	t_phil	*phil_step;

	if (!*phil)
	{
		*phil = ft_phil_new(phil, vars, num_philo);
		if (!*phil)
			return (1);
	}
	else
	{
		phil_step = *phil;
		while (phil_step->next)
			phil_step = phil_step->next;
		phil_step->next = ft_phil_new(phil, vars, num_philo);
		if (!phil_step->next)
			return (1);
	}
	return (0);
}
