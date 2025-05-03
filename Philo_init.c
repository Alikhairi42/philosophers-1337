/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:42:43 by a-khairi          #+#    #+#             */
/*   Updated: 2025/05/03 17:20:48 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	destroy_forks(t_fork *forks, int count)
{
	t_fork	*curr;
	t_fork	*next;
	int		i;

	curr = forks;
	i = 0;
	while (i < count)
	{
		next = curr->next;
		pthread_mutex_destroy(&curr->mutex);
		free(curr);
		curr = next;
		i++;
	}
}

int	init_forks(t_args *args)
{
	t_fork	*fork1;
	t_fork	*curr;
	int		i;

	i = 0;
	fork1 = malloc(sizeof(t_fork));
	if (!fork1)
		return (1);
	pthread_mutex_init(&fork1->mutex, NULL);
	args->forks = fork1;
	curr = fork1;
	while (++i < args->philo_count)
	{
		curr->next = malloc(sizeof(t_fork));
		if (!curr->next)
		{
			destroy_forks(args->forks, i);
			return (1);
		}
		curr = curr->next;
		pthread_mutex_init(&curr->mutex, NULL);
	}
	curr->next = fork1;
	pthread_mutex_init(&args->dead_mutex, NULL);
	return (0);
}

int	init_philo(t_args *args)
{
	int		i;
	t_fork	*curr;

	i = 0;
	curr = args->forks;
	args->philos = malloc(sizeof(t_philo) * args->philo_count);
	if (!args->philos)
		return (1);
	while (i < args->philo_count)
	{
		args->philos[i].id = i + 1;
		args->philos[i].eat_count = 0;
		args->philos[i].left_fork = &curr->mutex;
		args->philos[i].right_fork = &curr->next->mutex;
		args->philos[i].time_to_eat = args->time_to_eat;
		args->philos[i].time_to_sleep = args->time_to_sleep;
		args->philos[i].args = args;
		args->philos[i].last_meal = get_time();
		args->philos[i].start_time = get_time();
		pthread_mutex_init(&args->philos[i].last_time_mutex, NULL);
		curr = curr->next;
		i++;
	}
	return (0);
}

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		if (pthread_create(&args->philos[i].thread_id,
				NULL, &routine, &args->philos[i]) != 0)
			return (1);
		i++;
	}
	if (check_time(args))
	{
		destroy_forks(args->forks, args->philo_count);
		free(args->philos);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;
	int		i;

	args.is_dead = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	if (check_input(av, &args))
		return (1);
	if (init_forks(&args))
		return (1);
	if (init_philo(&args))
	{
		destroy_forks(args.forks, args.philo_count);
		return (1);
	}
	if (create_threads(&args))
	{
		destroy_forks(args.forks, args.philo_count);
		free(args.philos);
		return (1);
	}
	i = 0;
	while (i < args.philo_count)
	{
		pthread_join(args.philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(args.death_checker, NULL);
	destroy_forks(args.forks, args.philo_count);
	free(args.philos);
	return (0);
}
