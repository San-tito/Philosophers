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

t_philo	*init_philos(t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;
	t_philo		*philos;
	t_sem		*forks;

	i = 0;
	philos = xmalloc((*table).num_philos * sizeof(t_philo));
	forks = semaphore_init(SEM_FORKS, (*table).num_philos);
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).forks = forks;
		(*(philos + i)).table = table;
		(*(philos + i)).meal_count = 0;
	}
	(*table).log_sem = semaphore_init(SEM_LOG, 1);
	(*table).served_sem = semaphore_init(SEM_SERVED, 1);
	return (philos);
}

void	start_dinner(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	(*table).start_time = current_time() + ((*table).num_philos * 20);
	while (i < num_philos)
		(*(philos + i++)).last_meal = (*table).start_time;
	i = 0;
	while (i < num_philos)
	{
		(*(philos + i)).pid = make_child();
		if ((*(philos + i)).pid == 0)
			philosopher(philos + i, table);
		i++;
	}
}

void	cleanup_resources(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		waitchld((*(philos + i)).pid);
		i++;
	}
	semaphore_destroy(SEM_FORKS, (*philos).forks);
	semaphore_destroy(SEM_LOG, (*table).log_sem);
	semaphore_destroy(SEM_SERVED, (*table).served_sem);
	xfree(philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	table = set_table(argc, argv);
	philos = init_philos(&table);
	start_dinner(philos, &table);
	cleanup_resources(philos, &table);
	return (0);
}
