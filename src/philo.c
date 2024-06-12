/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 14:29:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*initialize_philosophers(t_table *shared_table)
{
	int			i;
	t_philo		*philos;
	t_mutex		*forks;
	const int	num_philos = (*shared_table).num_philos;

	i = 0;
	philos = xmalloc(num_philos * sizeof(t_philo));
	forks = xmalloc(num_philos * sizeof(t_mutex));
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = shared_table;
		(*(philos + i)).first_fork = forks + (i * (1 - (i & 1)) + ((i + 1)
					% num_philos) * (i & 1));
		(*(philos + i)).second_fork = forks + (((i + 1) % num_philos) * (1
					- (i & 1)) + i * (i & 1));
		(*(philos + i)).meal_count = 0;
		pthread_mutex_init(forks + i++, NULL);
	}
	pthread_mutex_init(&(*shared_table).log_lock, NULL);
	return (philos);
}

void	start_philosophers(t_philo *philos)
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
}

void	cleanup_resources(t_philo *philos)
{
	int			i;
	const int	num_philos = (*(*philos).table).num_philos;
	t_mutex		*forks;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_join((*(philos + i)).thread, NULL) != 0)
			fatal_error("Failed to join thread for philosopher %lu", i);
		i++;
	}
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
	t_table	shared_table;
	t_philo	*philosophers;

	shared_table = parse_arguments(argc, argv);
	philosophers = initialize_philosophers(&shared_table);
	start_philosophers(philosophers);
	cleanup_resources(philosophers);
	return (0);
}
