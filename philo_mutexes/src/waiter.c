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
	pthread_mutex_lock(&(*table).served_lock);
	served = (*table).dinner_served;
	pthread_mutex_unlock(&(*table).served_lock);
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
			pthread_mutex_lock(&(*(philo + i)).meal_lock);
			if (current_time() - (*(philo + i)).last_meal >= (*table).time_die)
			{
				log_state("died", philo + i, table);
				pthread_mutex_lock(&(*table).served_lock);
				(*table).dinner_served = 0;
				pthread_mutex_unlock(&(*table).served_lock);
			}
			pthread_mutex_unlock(&(*(philo + i)).meal_lock);
		}
		sleep_for((*table).time_die / 2, dinner_is_served(table));
	}
	return (0);
}
