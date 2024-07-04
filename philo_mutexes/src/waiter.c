/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 17:07:02 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_is_served(t_table *table)
{
	int	served;

	served = 0;
	thread_mutex_control(&(*table).served_lock, LOCK);
	served = (*table).dinner_served;
	thread_mutex_control(&(*table).served_lock, UNLOCK);
	return (served);
}

void	*waiter(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	time_t	start_time;
	int		i;

	philo = (t_philo *)arg;
	table = (*philo).table;
	start_time = (*table).start_time;
	while (current_time() < start_time)
		continue ;
	while (dinner_is_served(table))
	{
		i = 0;
		while (i < (*table).num_philos)
		{
			thread_mutex_control(&(*(philo + i)).meal_lock, LOCK);
			if (current_time() - (*(philo + i)).last_meal >= (*table).time_die)
			{
				log_state("died", philo + i, table);
				thread_mutex_control(&(*table).served_lock, LOCK);
				(*table).dinner_served = 0;
				thread_mutex_control(&(*table).served_lock, UNLOCK);
			}
			thread_mutex_control(&(*(philo + i)).meal_lock, UNLOCK);
		}
		sleep_for((*table).time_die / 2, dinner_is_served(table));
	}
	return (0);
}
