/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/11 13:11:17 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_served(t_table *table, int s)
{
	thread_mutex_control(&(*table).served_lock, LOCK);
	(*table).dinner_served = s;
	thread_mutex_control(&(*table).served_lock, UNLOCK);
}

int	dinner_is_served(t_table *table)
{
	int	served;

	served = 0;
	thread_mutex_control(&(*table).served_lock, LOCK);
	served = (*table).dinner_served;
	thread_mutex_control(&(*table).served_lock, UNLOCK);
	return (served);
}

int	is_thinker_dead(t_philo *philo, t_table *table, int *is_satiated)
{
	time_t	time;
	int		s;

	s = 0;
	thread_mutex_control(&(*philo).meal_lock, LOCK);
	time = current_time();
	if (time - (*philo).last_meal >= (*table).time_die)
	{
		set_served(table, 0);
		log_state("died", philo, table);
		s++;
	}
	if ((*philo).meal_count < (*table).num_must_eat)
		*is_satiated = 0;
	thread_mutex_control(&(*philo).meal_lock, UNLOCK);
	return (s);
}

void	arbitrator(t_philo *philo, t_table *table)
{
	int	i;
	int	satiated_thinkers;

	spinlock((*table).start_time);
	while (42)
	{
		i = 0;
		satiated_thinkers = 1;
		while (i < (*table).num_philos)
		{
			if (is_thinker_dead(philo + i, table, &satiated_thinkers))
				return ;
			i++;
		}
		if ((*table).num_must_eat && satiated_thinkers)
			return (set_served(table, 0));
		usleep((*table).time_die >> 1);
	}
}
