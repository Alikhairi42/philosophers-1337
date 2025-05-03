/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:47 by a-khairi          #+#    #+#             */
/*   Updated: 2025/05/03 17:20:09 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	ft_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_strdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_strdigit(str + i))
		return (LONG_MAX);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res >= INT_MAX || res <= INT_MIN)
			return (LONG_MAX);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
