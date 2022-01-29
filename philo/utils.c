/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleslee <jleslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:22:49 by jleslee           #+#    #+#             */
/*   Updated: 2022/01/25 16:12:59 by jleslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Получаем текущее юникс-время

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

// Определяем пробелы и пустые символы

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
			|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

// Засыпаем на заданное кол-во микросекунд

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

// Переводим строку в целочисленное

int	ft_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * i);
}

// Проверка на число

int	ft_is_digit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}
