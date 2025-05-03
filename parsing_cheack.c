/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cheack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:51:25 by a-khairi          #+#    #+#             */
/*   Updated: 2025/05/03 17:19:35 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_input(char **av, t_args *args)
{
	int		i;
	long	nbr;

	i = 1;
	while (av[i])
	{
		nbr = ft_atoi(av[i]);
		if (nbr == LONG_MAX)
		{
			printf("Error\n");
			return (1);
		}
		if (i == 1)
			args->philo_count = nbr;
		if (i == 2)
			args->time_to_die = nbr;
		if (i == 3)
			args->time_to_eat = nbr;
		if (i == 4)
			args->time_to_sleep = nbr;
		if (i == 5)
			args->eat_limit = nbr;
		i++;
	}
	return (0);
}
