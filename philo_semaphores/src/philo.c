/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 18:27:25 by santito          ###   ########.fr       */
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
	philos = xmalloc(num_philos * sizeof(t_philo));
	forks = xmalloc(num_philos * sizeof(t_sem));
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = table;
		(*(philos + i)).first_fork = forks + i;
		(*(philos + i)).second_fork = forks + ((i + 1) % num_philos);
		(*(philos + i)).meal_count = 0;
		semaphore_init(&(*(philos + i)).meal_sem, 1);
		semaphore_init(forks + i, 1);
		i++;
	}
	semaphore_init(&(*table).served_sem, 0);
	semaphore_init(&(*table).log_sem, 1);
	return (philos);
}

void	start_dinner(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	(*table).start_time = current_time() + ((*table).num_philos * 20);
	while (i < num_philos)
	{
		(*(philos + i)).last_meal = (*table).start_time;
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		(*(philos + i)).pid = fork();
		if ((*(philos + i)).pid < 0)
			internal_error("cannot create child process");
		else if ((*(philos + i)).pid == 0)
			philosopher(philos + i, table);
		i++;
	}
	semaphore_control(&(*table).served_sem, WAIT);
}

void	cleanup_resources(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;
	t_sem		*forks;

	i = 0;
	while (i < num_philos)
	{
		kill((*(philos + i)).pid, SIGTERM);
		waitpid((*(philos + i)).pid, 0, 0);
		i++;
	}
	i = 0;
	forks = (*philos).first_fork;
	while (i < num_philos)
	{
		semaphore_destroy(forks + i);
		semaphore_destroy(&(*(philos + i)).meal_sem);
		i++;
	}
	semaphore_destroy(&(*table).served_sem);
	semaphore_destroy(&(*table).log_sem);
	xfree(forks);
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
