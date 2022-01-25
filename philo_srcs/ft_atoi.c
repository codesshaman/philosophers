#include "philo.h"

// Пропускаем ненужные символы

static void	skip(int *index, const char *str)
{
	while (str[*index] == ' ' || str[*index] == '\t' || \
	str[*index] == '\v' || str[*index] == '\f' || \
	str[*index] == '\r' || str[*index] == '\n')
		*index += 1;
}

// проверяем знак числа

static int	check_sign(const char *str, int *index)
{
	if (str[*index] == '+')
		*index += 1;
	if (!str[*index] || str[*index] == '-')
		return (1);
	return (0);
}

// Переводим строку в число

unsigned int	ft_atoi(const char *str, int *i)
{
	int					index;
	int					sign;
	unsigned long long	num;

	*i = 0;
	sign = 1;
	num = 0;
	index = 0;
	skip(&index, str);
	if (check_sign(str, &index))
		*i = -1;
	while (str[index] >= '0' && str[index] <= '9')
	{
		num = num * 10 + (str[index] - '0');
		index++;
	}
	if ((str[index] < '0' || str[index] > '9') && str[index])
		*i = -1;
	if ((num > 4294967295 && sign > 0) || (num > 0 && sign < 0))
		*i = -1;
	return ((unsigned int)num * sign);
}
