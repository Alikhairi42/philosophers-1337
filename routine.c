/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:22:18 by a-khairi          #+#    #+#             */
/*   Updated: 2025/05/03 15:22:18 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	my_printf(t_philo *philo, char *str)
{
	long	now;

	pthread_mutex_lock(&philo->args->dead_mutex);
	now = get_time() - philo->start_time;
	if (philo->args->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_mutex);
		return (1);
	}
	printf("%ld ms %d %s", now, philo->id, str);
	pthread_mutex_unlock(&philo->args->dead_mutex);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		usleep(1000);
		pthread_mutex_lock(philo->left_fork);
		if (my_printf(philo, "has taken a fork\n"))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		if (my_printf(philo, "has taken a fork\n"))
			return (unlock_forks(philo), 1);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (my_printf(philo, "has taken a fork\n"))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		if (my_printf(philo, "has taken a fork\n"))
		{
			unlock_forks(philo);
			return (1);
		}
	}
	return (0);
}

int	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_time_mutex);
	if (my_printf(philo, "is eating\n"))
	{
		unlock_forks(philo);
		return (1);
	}
	if (philo->time_to_eat < philo->args->time_to_die)
		usleep(philo->time_to_eat * 1000);
	else
		usleep(philo->args->time_to_die * 1000);
	pthread_mutex_lock(&philo->args->dead_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->args->dead_mutex);
	unlock_forks(philo);
	return (0);
}

void	sleeping_thinking(t_philo *philo)
{
	if (!my_printf(philo, "is sleeping\n"))
	{
		if (philo->time_to_sleep < philo->args->time_to_die)
			usleep(philo->time_to_sleep * 1000);
		else
			usleep(philo->args->time_to_die * 1000);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (my_printf(philo, "is thinking\n"))
			break ;
		if (philo->args->philo_count % 2)
		{
			if (philo->time_to_eat < philo->args->time_to_die)
				usleep(philo->time_to_eat * 1000);
			else
				usleep(philo->args->time_to_die * 1000);
		}
		if (one_philo(philo))
			break ;
		if (take_forks(philo))
			break ;
		if (start_eating(philo))
			break ;
		sleeping_thinking(philo);
	}
	return (NULL);
}
