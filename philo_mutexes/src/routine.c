/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/11 12:35:20 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(const char *state, t_philo *philo, t_table *table)
{
	thread_mutex_control(&(*table).log_lock, LOCK);
	if (*state == 'd' || dinner_is_served(table))
	{
		printf("%ld ", current_time() - (*table).start_time);
		printf("%d ", (*philo).id);
		printf("%s ", state);
		printf("\n");
	}
	thread_mutex_control(&(*table).log_lock, UNLOCK);
}

void	dine_with_single_fork(t_philo *philo, t_table *table)
{
	int64_t	time;

	time = (*table).time_die + (*table).time_eat + (*table).time_sleep;
	sleep_for(time, table);
	thread_mutex_control((*philo).first_fork, UNLOCK);
}

void	dine(t_philo *philo, t_table *table)
{
	thread_mutex_control((*philo).first_fork, LOCK);
	log_state("has taken a fork", philo, table);
	if ((*table).num_philos == 1)
		return (dine_with_single_fork(philo, table));
	thread_mutex_control((*philo).second_fork, LOCK);
	log_state("has taken a fork", philo, table);
	log_state("is eating", philo, table);
	sleep_for((*table).time_eat, table);
	thread_mutex_control(&(*philo).meal_lock, LOCK);
	(*philo).last_meal = current_time();
	(*philo).meal_count++;
	thread_mutex_control(&(*philo).meal_lock, UNLOCK);
	thread_mutex_control((*philo).second_fork, UNLOCK);
	thread_mutex_control((*philo).first_fork, UNLOCK);
}

void	rest(t_philo *philo, t_table *table)
{
	log_state("is sleeping", philo, table);
	sleep_for((*table).time_sleep, table);
	log_state("is thinking", philo, table);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (*philo).table;
	spinlock((*table).start_time);
	if ((*philo).id & 1)
		sleep_for((*table).time_eat >> 1, table);
	while (dinner_is_served(table))
	{
		dine(philo, table);
		rest(philo, table);
	}
	return (0);
}
