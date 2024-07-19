/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 16:00:38 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_thinkers(t_philo *philos, t_table *table)
{
	int			i;
	const int	num_philos = (*table).num_philos;

	i = 0;
	while (i < num_philos)
	{
		kill((*(philos + i)).pid, SIGKILL);
		i++;
	}
}

int	is_thinker_dead(t_philo *philo, t_table *table, int *is_satiated)
{
	time_t	time;

	semaphore_control(&(*philo).meal_sem, WAIT);
	time = current_time();
	if (time - (*philo).last_meal >= (*table).time_die)
	{
		semaphore_control(&(*philo).meal_sem, POST);
		return (1);
	}
	if ((*philo).meal_count < (*table).num_must_eat)
		*is_satiated = 0;
	semaphore_control(&(*philo).meal_sem, POST);
	return (0);
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
			{
				log_state("died", philo + i, table);
				return (kill_thinkers(philo, table));
			}
			i++;
		}
		if ((*table).num_must_eat && satiated_thinkers)
			return (kill_thinkers(philo, table));
		usleep((*table).time_die >> 1);
	}
}
