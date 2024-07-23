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

void	is_thinker_dead(t_philo *philo, t_table *table)
{
	time_t	time;

	semaphore_control((*philo).meal_sem, WAIT);
	time = current_time();
	if (time - (*philo).last_meal >= (*table).time_die)
	{
		log_state("died", philo, table);
		semaphore_control((*table).served_sem, POST);
	}
	semaphore_control((*philo).meal_sem, POST);
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
		is_thinker_dead(philo, table);
		usleep((*table).time_die >> 1);
	}
	return (0);
}
