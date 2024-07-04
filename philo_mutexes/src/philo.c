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

int	init_philos(t_table *table, t_philo *philos)
{
	int			i;
	t_mutex		*forks;
	const int	num_philos = (*table).num_philos;

	i = 0;
	forks = xmalloc(num_philos * sizeof(t_mutex));
	while (i < num_philos && forks)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = table;
		(*(philos + i)).first_fork = forks + (i * (1 - (i & 1)) + ((i + 1)
					% num_philos) * (i & 1));
		(*(philos + i)).second_fork = forks + (((i + 1) % num_philos) * (1
					- (i & 1)) + i * (i & 1));
		(*(philos + i)).meal_count = 0;
		(*(philos + i)).last_meal = (*table).start_time;
		if (thread_mutex_init(&(*(philos + i)).meal_lock)
			|| thread_mutex_init(forks + i++))
			return (1);
	}
	if (forks == 0 || thread_mutex_init(&(*table).served_lock)
		|| thread_mutex_init(&(*table).log_lock))
		return (1);
	return (0);
}

int	start_dinner(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		if (thread_create(&((*(philos + i)).thread), philosopher, philos + i))
			return (1);
		i++;
	}
	if (thread_create(&(*table).waiter_thread, waiter, philos))
		return (1);
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
		if (thread_join((*(philos + i)).thread))
			return (1);
		i++;
	}
	if (thread_join((*table).waiter_thread) != 0)
		return (1);
	i = 0;
	forks = (*philos).first_fork;
	while (i < num_philos)
	{
		if (thread_mutex_destroy(forks + i))
			return (1);
		i++;
	}
	if (thread_mutex_destroy(&(*table).log_lock)
		|| thread_mutex_destroy(&(*table).served_lock))
		return (1);
	return (xfree(forks), xfree(philos), 0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	if (set_table(argc, argv, &table))
		return (2);
	philos = xmalloc(table.num_philos * sizeof(t_philo));
	if (philos == 0)
		return (2);
	if (init_philos(&table, philos) || start_dinner(philos, &table)
		|| cleanup_resources(philos, &table))
		return (2);
	return (0);
}
