/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:25:27 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/28 13:41:52 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000ULL + time.tv_usec / 1000);
}

void	log_state(const t_philo *philosopher)
{
	if (philosopher->state == FORK_TAKEN)
		printf("%ld %d has taken a fork\n", get_current_time(),
			philosopher->id);
	else if (philosopher->state == EATING)
		printf("%ld %d is eating\n", get_current_time(),
			philosopher->id);
	else if (philosopher->state == SLEEPING)
		printf("%ld %d is sleeping\n", get_current_time(),
			philosopher->id);
	else if (philosopher->state == THINKING)
		printf("%ld %d is thinking\n", get_current_time(),
			philosopher->id);
	else if (philosopher->state == DEAD)
		printf("%ld %d died\n", get_current_time(),
			philosopher->id);
}
