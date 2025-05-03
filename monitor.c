/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:27:45 by a-khairi          #+#    #+#             */
/*   Updated: 2025/05/03 15:27:45 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static int	check_death(t_args *args, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&args->philos[i].last_time_mutex);
	time_since_last_meal = get_time() - args->philos[i].last_meal;
	pthread_mutex_unlock(&args->philos[i].last_time_mutex);
	pthread_mutex_lock(&args->dead_mutex);
	if ((time_since_last_meal > args->time_to_die && !args->is_dead)
		|| args->philos->eat_count == args->eat_limit)
	{
		if (time_since_last_meal > args->time_to_die && !args->is_dead)
			printf("%ld ms %d dead\n",
				get_time() - args->philos[i].start_time,
				args->philos[i].id);
		args->is_dead = 1;
		pthread_mutex_unlock(&args->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&args->dead_mutex);
	return (0);
}

void	*kill_philos(void *arg)
{
	t_args	*args;
	int		i;

	args = (t_args *)arg;
	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			if (check_death(args, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_time(t_args *args)
{
	if (pthread_create(&args->death_checker, NULL, &kill_philos, args) != 0)
		return (1);
	return (0);
}
