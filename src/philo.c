/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/27 17:32:38 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*setup_philosophers(int num_philos)
{
	t_philo	*head;
	t_philo	*current;
	t_philo	*new;
	int		i;

	head = NULL;
	i = 0;
	while (i < num_philos)
	{
		new = xmalloc(sizeof(t_philo));
		(*new).id = i;
		(*new).next = 0;
		if (head == 0)
			head = new;
		else
			(*current).next = new;
		current = new;
		i++;
	}
	return (head);
}

void	launch_philosophers(t_philo *philos, t_params params)
{
	t_philo	*current;

	(void)params;
	current = philos;
	while (current)
	{
		pthread_create(&(*current).thread, NULL, philosopher, current);
		current = (*current).next;
	}
	current = philos;
	while (current)
	{
		pthread_join((*current).thread, NULL);
		current = (*current).next;
	}
}

void	cleanup_philosophers(t_philo *philos)
{
	t_philo	*tmp;

	while (philos)
	{
		tmp = philos;
		philos = (*philos).next;
		xfree(tmp);
	}
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philos;

	params = parse_arguments(argc, argv);
	philos = setup_philosophers(params.num_philos);
	launch_philosophers(philos, params);
	cleanup_philosophers(philos);
	return (0);
}
