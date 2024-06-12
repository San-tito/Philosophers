/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 17:14:53 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_state(const char *state, t_philo philo, t_table table)
{
	pthread_mutex_lock(&table.log_lock);
	printf("%ld %d %s\n", current_time() - table.start_time, philo.id, state);
	pthread_mutex_unlock(&table.log_lock);
}

void	dine(t_philo philo, t_table table)
{
	pthread_mutex_lock(philo.first_fork);
	log_state("has taken a fork", philo, table);
	pthread_mutex_lock(philo.second_fork);
	log_state("has taken a fork", philo, table);
	log_state("is eating", philo, table);
	philo.last_meal = current_time();
	sleep_for(table.time_eat);
	philo.meal_count++;
	pthread_mutex_unlock(philo.first_fork);
	pthread_mutex_unlock(philo.second_fork);
}

void	rest(t_philo philo, t_table table)
{
	log_state("is sleeping", philo, table);
	sleep_for(table.time_sleep);
	log_state("is thinking", philo, table);
}

void	*philosopher(void *arg)
{
	t_philo	philo;
	t_table	table;
	time_t	start_time;

	philo = *(t_philo *)arg;
	table = *philo.table;
	start_time = table.start_time;
	if (philo.id & 1)
		start_time += table.time_eat;
	while (current_time() < start_time)
		continue ;
	while (table.dinner_served)
	{
		dine(philo, table);
		rest(philo, table);
	}
	return (0);
}
