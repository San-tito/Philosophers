/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:56:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 18:15:20 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_for(int64_t milliseconds)
{
	time_t	end_time;

	end_time = current_time() + milliseconds;
	while (current_time() < end_time)
		usleep(100);
}

void	spinlock(time_t start_time)
{
	while (current_time() < start_time)
		continue ;
}
