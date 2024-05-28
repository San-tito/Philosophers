/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/28 13:18:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*setup_philosophers(t_params params)
{
	t_philo		*philos;
	t_fork		*forks;
	int			i;
	const int	num_philos = params.num_philos;

	i = 0;
	philos = xmalloc(num_philos * sizeof(t_philo));
	forks = xmalloc(num_philos * sizeof(t_fork));
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).params = params;
		pthread_mutex_init(forks + i, NULL);
		(*(philos + i)).left_fork = forks + ((i - 1 + num_philos) % num_philos);
		(*(philos + i)).right_fork = forks + ((i + 1) % num_philos);
		i++;
	}
	return (philos);
}

void	launch_philosophers(t_philo *philos)
{
	int			i;
	const int	num_philos = (*philos).params.num_philos;

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

void	cleanup_philosophers(t_philo *philos)
{
	int			i;
	const int	num_philos = (*philos).params.num_philos;

	i = 0;
	while (i < num_philos)
	{
		// if (pthread_detach(philos[i].thread) != 0)
		// fatal_error("Failed to detach thread for philosopher %lu", i);
		if (pthread_mutex_destroy((*(philos + i)).left_fork) != 0)
			fatal_error("Failed to destroy fork of philosopher %lu", i);
		i++;
	}
	xfree((*philos).left_fork);
	xfree(philos);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	params = parse_arguments(argc, argv);
	philos = setup_philosophers(params);
	launch_philosophers(philos);
	cleanup_philosophers(philos);
	return (0);
}
