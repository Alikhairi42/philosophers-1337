/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:56:36 by a-khairi          #+#    #+#             */
/*   Updated: 2025/05/03 17:58:51 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	struct s_fork	*next;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			time_to_eat;
	int				time_to_sleep;
	long			last_meal;
	pthread_mutex_t	last_time_mutex;
	pthread_mutex_t	*left_fork;
	pthread_t		thread_id;
	long			start_time;
	pthread_mutex_t	*right_fork;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_mutex_t	dead_mutex;
	int				is_dead;
	pthread_t		death_checker;
	int				eat_limit;
	t_fork			*forks;
	t_philo			*philos;
}	t_args;

// Ft_routine
void		*routine(void *arg);
int			my_printf(t_philo *philo, char *str);
int			one_philo(t_philo *philo);
void		unlock_forks(t_philo *philo);
int			take_forks(t_philo *philo);
int			start_eating(t_philo *philo);
void		sleeping_thinking(t_philo *philo);

// Philo_init
int			init_forks(t_args *args);
int			init_philo(t_args *args);
int			create_threads(t_args *args);

// Ft_monitor
void		*kill_philos(void *arg);
int			check_time(t_args *args);
void		destroy_forks(t_fork *forks, int count);
long		get_time(void);

// Ft_utlise
size_t		ft_strlen(const char *s);
long		ft_atoi(char *str);
int			check_input(char **av, t_args *args);

#endif
