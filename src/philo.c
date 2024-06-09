/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/09 02:07:32 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*thinkers_assembly(t_table *table)
{
	int			i;
	t_philo		*philos;
	t_fork		*forks;
	const int	num_philos = (*table).num_philos;

	i = 0;
	philos = xmalloc(num_philos * sizeof(t_philo));
	forks = xmalloc(num_philos * sizeof(t_fork));
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = table;
		pthread_mutex_init(forks + i, NULL);
		(*(philos + i)).first_fork = forks + (i * (1 - (i & 1)) + ((i + 1)
					% num_philos) * (i & 1));
		(*(philos + i)).second_fork = forks + (((i + 1) % num_philos) * (1
					- (i & 1)) + i * (i & 1));
		(*(philos + i)).meal_count = 0;
		i++;
	}
	pthread_mutex_init(&(*table).micro, NULL);
	return (philos);
}

void	gathering_of_sages(t_philo *philos)
{
	int			i;
	const int	num_philos = (*(*philos).table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&((*(philos + i)).thread), NULL, philosopher, philos
				+ i) != 0)
			fatal_error("Failed to create thread for philosopher %lu", i);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		if (pthread_join((*(philos + i)).thread, NULL) != 0)
			fatal_error("Failed to join thread for philosopher %lu", i);
		i++;
	}
}

void	purge_intellectuals(t_philo *philos)
{
	int			i;
	const int	num_philos = (*(*philos).table).num_philos;
	t_fork		*forks;

	i = 0;
	forks = (*philos).first_fork;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(forks + i) != 0)
			fatal_error("Failed to destroy fork of philosopher %lu", i);
		i++;
	}
	xfree(forks);
	xfree(philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	table = parse_arguments(argc, argv);
	philos = thinkers_assembly(&table);
	gathering_of_sages(philos);
	purge_intellectuals(philos);
	return (0);
}
