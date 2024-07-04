/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 18:06:27 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(const char *state, t_philo *philo, t_table *table)
{
	if (dinner_is_served(table))
	{
		pthread_mutex_lock(&(*table).log_lock);
		printf("%ld ", current_time() - (*table).start_time);
		printf("%d ", (*philo).id);
		printf("%s ", state);
		printf("\n");
		pthread_mutex_unlock(&(*table).log_lock);
	}
}

void	dine(t_philo *philo, t_table *table)
{
	pthread_mutex_lock((*philo).first_fork);
	log_state("has taken a fork", philo, table);
	pthread_mutex_lock((*philo).second_fork);
	log_state("has taken a fork", philo, table);
	log_state("is eating", philo, table);
	pthread_mutex_lock(&(*philo).meal_lock);
	(*philo).last_meal = current_time();
	pthread_mutex_unlock(&(*philo).meal_lock);
	sleep_for((*table).time_eat, dinner_is_served(table));
	pthread_mutex_lock(&(*philo).meal_lock);
	(*philo).meal_count++;
	pthread_mutex_unlock(&(*philo).meal_lock);
	pthread_mutex_unlock((*philo).first_fork);
	pthread_mutex_unlock((*philo).second_fork);
}

void	rest(t_philo *philo, t_table *table)
{
	log_state("is sleeping", philo, table);
	sleep_for((*table).time_sleep, dinner_is_served(table));
	log_state("is thinking", philo, table);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	time_t	start_time;

	philo = (t_philo *)arg;
	table = (*philo).table;
	start_time = (*table).start_time;
	if ((*philo).id & 1)
		start_time += (*table).time_eat;
	while (current_time() < start_time)
		continue ;
	while (dinner_is_served(table))
	{
		dine(philo, table);
		rest(philo, table);
	}
	return (0);
}
