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

char	*generate_sem_name(int id)
{
	static char	sem_name[32] = SEM_MEAL;
	const int	len = sizeof(SEM_MEAL) - 1;
	int			i;
	int			count;

	i = id;
	count = 0;
	while (i > 0)
	{
		count++;
		i /= 10;
	}
	if (id == 0)
		count++;
	i = len + count - 1;
	while (i >= len)
	{
		*(sem_name + i) = '0' + (id % 10);
		id /= 10;
		i--;
	}
	return (sem_name);
}

t_philo	*init_philos(t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;
	t_philo		*philos;
	t_sem		*forks;

	i = 0;
	philos = xmalloc(num_philos * sizeof(t_philo));
	forks = semaphore_init(SEM_FORKS, num_philos);
	(*table).log_sem = semaphore_init(SEM_LOG, 1);
	(*table).served_sem = semaphore_init(SEM_SERVED, 0);
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = table;
		(*(philos + i)).forks = forks;
		(*(philos + i)).meal_count = 0;
		(*(philos + i)).meal_sem = semaphore_init(generate_sem_name(i), 1);
		i++;
	}
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
	semaphore_control((*table).served_sem, WAIT);
}

void	cleanup_resources(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		kill((*(philos + i)).pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		semaphore_destroy((*(philos + i)).meal_sem);
		i++;
	}
	semaphore_destroy((*philos).forks);
	semaphore_destroy((*table).log_sem);
	semaphore_destroy((*table).served_sem);
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
