/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satori.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/27 17:30:29 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		printf("%d is thinking\n", philo->id);
		usleep(1000 * (philo->id + 1));
		printf("%d is hungry\n", philo->id);
		printf("%d is eating\n", philo->id);
		usleep(1000 * (philo->id + 1));
		printf("%d is sleeping\n", philo->id);
		usleep(1000 * (philo->id + 1));
	}
	return (0);
}
