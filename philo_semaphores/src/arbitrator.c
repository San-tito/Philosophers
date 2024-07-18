/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/18 15:46:12 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_served(t_table *table, int s)
{
	semaphore_control(&(*table).served_sem, WAIT);
	(*table).dinner_served = s;
	semaphore_control(&(*table).served_sem, POST);
}

int	dinner_is_served(t_table *table)
{
	int	served;

	served = 0;
	semaphore_control(&(*table).served_sem, WAIT);
	served = (*table).dinner_served;
	semaphore_control(&(*table).served_sem, POST);
	return (served);
}

int	is_thinker_dead(t_philo *philo, t_table *table, int *is_satiated)
{
	time_t	time;
	int		s;

	s = 0;
	semaphore_control(&(*philo).meal_sem, WAIT);
	time = current_time();
	if (time - (*philo).last_meal >= (*table).time_die)
	{
		set_served(table, 0);
		log_state("died", philo, table);
		s++;
	}
	if ((*philo).meal_count < (*table).num_must_eat)
		*is_satiated = 0;
	semaphore_control(&(*philo).meal_sem, POST);
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
