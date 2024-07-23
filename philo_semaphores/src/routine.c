/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 18:28:03 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(const char *state, t_philo *philo, t_table *table)
{
	semaphore_control((*table).log_sem, WAIT);
	printf("%ld ", current_time() - (*table).start_time);
	printf("%d ", (*philo).id);
	printf("%s ", state);
	printf("\n");
	semaphore_control((*table).log_sem, POST);
}

void	dine_with_single_fork(t_philo *philo, t_table *table)
{
	int64_t	time;

	time = (*table).time_die + (*table).time_eat + (*table).time_sleep;
	sleep_for(time);
	semaphore_control((*philo).forks, POST);
}

void	dine(t_philo *philo, t_table *table)
{
	semaphore_control((*philo).forks, WAIT);
	log_state("has taken a fork", philo, table);
	if ((*table).num_philos == 1)
		return (dine_with_single_fork(philo, table));
	semaphore_control((*philo).forks, WAIT);
	log_state("has taken a fork", philo, table);
	log_state("is eating", philo, table);
	sleep_for((*table).time_eat);
	semaphore_control((*philo).meal_sem, WAIT);
	(*philo).last_meal = current_time();
	(*philo).meal_count++;
	semaphore_control((*philo).meal_sem, POST);
	semaphore_control((*philo).forks, POST);
	semaphore_control((*philo).forks, POST);
}

void	rest(t_philo *philo, t_table *table)
{
	log_state("is sleeping", philo, table);
	sleep_for((*table).time_sleep);
	log_state("is thinking", philo, table);
}

void	philosopher(t_philo *philo, t_table *table)
{
	t_thread	monitor;

	thread_create(&monitor, arbitrator, philo);
	thread_detach(monitor);
	spinlock((*table).start_time);
	if ((*philo).id & 1)
		sleep_for((*table).time_eat >> 1);
	while (42)
	{
		dine(philo, table);
		rest(philo, table);
	}
}
