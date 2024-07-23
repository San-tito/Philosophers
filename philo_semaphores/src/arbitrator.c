/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 18:27:47 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinker_dead(t_philo *philo, t_table *table)
{
	time_t	time;
	int		s;

	s = 0;
	semaphore_control((*philo).meal_sem, WAIT);
	time = current_time();
	if (time - (*philo).last_meal >= (*table).time_die)
	{
		log_state("died", philo, table);
		s++;
	}
	semaphore_control((*philo).meal_sem, POST);
	return (s);
}

void	*arbitrator(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (*philo).table;
	spinlock((*table).start_time);
	while (42)
	{
		if (is_thinker_dead(philo, table))
			return (0);
		usleep((*table).time_die >> 1);
	}
	return (0);
}
