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
	t_philo	*philos;
	t_table	*table;
	int		i;

	philos = (t_philo *)arg;
	table = (*philos).table;
	while ((*table).dinner_served)
	{
		i = 0;
		while (i < (*table).num_philos)
		{
			pthread_mutex_lock(&(*table).dinner_lock);
			if (current_time() - (*(philos + i)).last_meal > (*table).time_die)
				(*(*philos).table).dinner_served = 0;
			pthread_mutex_unlock(&(*table).dinner_lock);
		}
		sleep_for((*table).time_die / 2, (*table).dinner_served);
	}
	return (0);
}

t_philo	*initialize_philosophers(t_table *table)
{
	int			i;
	t_philo		*philos;
	t_mutex		*forks;
	const int	num_philos = (*table).num_philos;

	i = 0;
	philos = xmalloc(num_philos * sizeof(t_philo));
	forks = xmalloc(num_philos * sizeof(t_mutex));
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = table;
		(*(philos + i)).first_fork = forks + (i * (1 - (i & 1)) + ((i + 1)
					% num_philos) * (i & 1));
		(*(philos + i)).second_fork = forks + (((i + 1) % num_philos) * (1
					- (i & 1)) + i * (i & 1));
		(*(philos + i)).meal_count = 0;
		(*(philos + i)).last_meal = (*table).start_time;
		pthread_mutex_init(forks + i++, NULL);
	}
	pthread_mutex_init(&(*table).log_lock, NULL);
	pthread_mutex_init(&(*table).dinner_lock, NULL);
	return (philos);
}

void	start_philosophers(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&((*(philos + i)).thread), NULL, philosopher, philos
				+ i) != 0)
			fatal_error("Failed to create thread for philosopher %lu", i);
		i++;
	}
	if (pthread_create(&(*table).waiter_thread, NULL, waiter, philos) != 0)
		internal_error("Failed to create waiter thread");
}

void	cleanup_resources(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;
	t_mutex		*forks;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_join((*(philos + i)).thread, NULL) != 0)
			fatal_error("Failed to join thread for philosopher %lu", i);
		i++;
	}
	if (pthread_join((*table).waiter_thread, NULL) != 0)
		internal_error("Failed to join waiter thread");
	i = 0;
	forks = (*philos).first_fork;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(forks + i) != 0)
			fatal_error("Failed to destroy fork of philosopher %lu", i);
		i++;
	}
	if (pthread_mutex_destroy(&(*table).log_lock) != 0)
		internal_error("Failed to destroy log lock");
	xfree(forks);
	xfree(philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philosophers;

	table = parse_arguments(argc, argv);
	philosophers = initialize_philosophers(&table);
	start_philosophers(philosophers, &table);
	cleanup_resources(philosophers, &table);
	return (0);
}
