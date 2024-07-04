/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 18:07:43 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*waiter(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	time_t	start_time;
	int		i;

	philo = (t_philo *)arg;
	table = (*philo).table;
	start_time = (*table).start_time;
	while (current_time() < start_time)
		continue ;
	while (dinner_is_served(table))
	{
		i = 0;
		while (i < (*table).num_philos)
		{
			pthread_mutex_lock(&(*(philo + i)).meal_lock);
			if (current_time() - (*(philo + i)).last_meal > (*table).time_die)
			{
				pthread_mutex_lock(&(*table).served_lock);
				(*table).dinner_served = 0;
				pthread_mutex_unlock(&(*table).served_lock);
			}
			pthread_mutex_unlock(&(*(philo + i)).meal_lock);
		}
		sleep_for((*table).time_die / 2, dinner_is_served(table));
	}
	return (0);
}

int	init_philos(t_table *table, t_philo **philos)
{
	int			i;
	t_mutex		*forks;
	const int	num_philos = (*table).num_philos;

	i = 0;
	*philos = xmalloc(num_philos * sizeof(t_philo));
	if (philos == 0)
		return (1);
	forks = xmalloc(num_philos * sizeof(t_mutex));
	if (forks == 0)
		return (1);
	while (i < num_philos)
	{
		(*(*philos + i)).id = i;
		(*(*philos + i)).table = table;
		(*(*philos + i)).first_fork = forks + (i * (1 - (i & 1)) + ((i + 1)
					% num_philos) * (i & 1));
		(*(*philos + i)).second_fork = forks + (((i + 1) % num_philos) * (1
					- (i & 1)) + i * (i & 1));
		(*(*philos + i)).meal_count = 0;
		(*(*philos + i)).last_meal = (*table).start_time;
		if (pthread_mutex_init(&(*(*philos + i)).meal_lock, NULL))
			return (internal_error("Failed to meal lock %lu"), 1);
		if (pthread_mutex_init(forks + i++, NULL))
			return (fatal_error("Failed to init fork %lu", i), 1);
	}
	if (pthread_mutex_init(&(*table).served_lock, NULL))
		return (internal_error("Failed to init served_lock;"), 1);
	if (pthread_mutex_init(&(*table).log_lock, NULL))
		return (internal_error("Failed to init log lock"), 1);
	return (0);
}

int	start_dinner(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&((*(philos + i)).thread), NULL, philosopher, philos
				+ i))
			return (fatal_error("Failed to create thread for philosopher %lu",
					i), 1);
		i++;
	}
	if (pthread_create(&(*table).waiter_thread, NULL, waiter, philos) != 0)
		internal_error("Failed to create waiter thread");
	return (0);
}

int	cleanup_resources(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;
	t_mutex		*forks;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_join((*(philos + i)).thread, NULL))
			return (fatal_error("Failed to join thread for philosopher %lu", i),
				1);
		i++;
	}
	if (pthread_join((*table).waiter_thread, NULL) != 0)
		internal_error("Failed to join waiter thread");
	i = 0;
	forks = (*philos).first_fork;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(forks + i))
			return (fatal_error("Failed to destroy fork of philosopher %lu", i),
				1);
		i++;
	}
	if (pthread_mutex_destroy(&(*table).log_lock))
		return (internal_error("Failed to destroy log lock"), 1);
	return (xfree(forks), xfree(philos), 0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	if (set_table(argc, argv, &table) || init_philos(&table, &philos)
		|| start_dinner(philos, &table) || cleanup_resources(philos, &table))
		return (2);
	return (0);
}
