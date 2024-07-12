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
	if (*state == 'd' || dinner_is_served(table))
	{
		printf("%ld ", current_time() - (*table).start_time);
		printf("%d ", (*philo).id);
		printf("%s ", state);
		printf("\n");
	}
}

void	philosopher(t_philo *philo, t_table *table)
{
	spinlock((*table).start_time);
	(void)philo;
}
