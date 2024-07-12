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

	i = 0;
	philos = xmalloc((*table).num_philos * sizeof(t_philo));
	while (i < num_philos)
	{
		(*(philos + i)).id = i;
		(*(philos + i)).table = table;
		(*(philos + i)).meal_count = 0;
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
		(*(philos + i++)).last_meal = (*table).start_time;
	i = 0;
	while (i < num_philos)
	{
		(*(philos + i)).pid = make_child();
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
