

#include "philo.h"

// Проверяем статус философа

static int	ft_check_status(const int *status)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (status[i] < 0)
			return (1);
	return (0);
}

// Заполняем структуры данными из аргументов

int	ft_init_vars(t_vars *vars, int argc, char **argv)
{
	int	status[5];

	vars->num_of_philos = ft_atoi(argv[1], &status[0]);
	vars->time_to_die = ft_atoi(argv[2], &status[1]);
	vars->time_to_eat = ft_atoi(argv[3], &status[2]);
	vars->time_to_sleep = ft_atoi(argv[4], &status[3]);
	if (argc > 5)
		vars->num_time_to_eat = ft_atoi(argv[5], &status[4]);
	else
	{
		vars->num_time_to_eat = -1;
		status[4] = 0;
	}
	if (ft_check_status(status) || vars->time_to_sleep > MAX || \
			vars->time_to_die > MAX || vars->time_to_eat > MAX || \
				vars->num_of_philos == 0 || \
					pthread_mutex_init(&vars->mutex_out, NULL) || \
						!vars->num_time_to_eat)
		return (1);
	vars->dead = 0;
	vars->end = 0;
	return (0);
}

// Инициализация структуры философа

int	ft_init_phils(t_vars *vars, t_phil **phil)
{
	unsigned int	i;

	i = -1;
	while (++i < vars->num_of_philos)
		if (ft_phil_add_back(phil, i, vars))
			return (ft_phil_lstclear(phil, 1));
	(*phil)->prev = ft_phil_last(phil);
	(*phil)->prev->next = *phil;
	return (0);
}

// Подсчитываем длинну строки

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// Выводим ошибку

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}