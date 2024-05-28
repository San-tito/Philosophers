/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satori.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/28 13:40:46 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	const t_philo	*philo = (t_philo *)arg;
	const t_params	params = (*philo).params;

	printf("Philosopher %d started with params:\n", philo->id);
	printf("  Number of philosophers: %d\n", params.num_philos);
	printf("  Time to die: %d\n", params.time_die);
	printf("  Time to eat: %d\n", params.time_eat);
	printf("  Time to sleep: %d\n", params.time_sleep);
	printf("  Number of times to eat: %d\n", params.num_must_eat);
	log_state(philo);
	return (0);
}
