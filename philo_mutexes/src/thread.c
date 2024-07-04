/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 18:06:27 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_mutex_init(t_mutex *mutexp)
{
	int	status;

	status = pthread_mutex_init(mutexp, NULL);
	if (status)
		fatal_error("cannot initialize %lu mutex", (unsigned long)mutexp);
	return (status);
}

int	thread_mutex_control(t_mutex *mutexp, t_mutex_action action)
{
	int	status;

	if (action == LOCK)
	{
		status = pthread_mutex_lock(mutexp);
		if (status)
			fatal_error("cannot lock %lu mutex", (unsigned long)mutexp);
	}
	else if (action == UNLOCK)
	{
		status = pthread_mutex_unlock(mutexp);
		if (status)
			fatal_error("cannot unlock %lu mutex", (unsigned long)mutexp);
	}
	return (status);
}

int	thread_mutex_destroy(t_mutex *mutexp)
{
	int	status;

	status = pthread_mutex_destroy(mutexp);
	if (status)
		fatal_error("cannot destroy %lu mutex", (unsigned long)mutexp);
	return (status);
}

int	thread_create(t_thread *threadp, void *(*start_routine)(void *), void *arg)
{
	int	status;

	status = pthread_create(threadp, NULL, start_routine, arg);
	if (status)
		fatal_error("cannot create %lu thread", (unsigned long)threadp);
	return (status);
}

int	thread_join(t_thread thread)
{
	int	status;

	status = pthread_join(thread, NULL);
	if (status)
		fatal_error("cannot join %lu thread", (unsigned long)thread);
	return (status);
}
