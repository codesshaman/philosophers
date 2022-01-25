

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_phil	*phil;

	if (argc < 5 || argc > 6)
		return (ft_error("Error. Wrong number arguments.\n"));
	if (ft_init_vars(&vars, argc, argv))
		return (ft_error("Error. Wrong arguments.\n"));
	ft_do(&vars, &phil);
	phil->prev->next = NULL;
	ft_phil_lstclear(&phil, 0);
}
