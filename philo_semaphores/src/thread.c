/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 17:44:48 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_thread *threadp, void *(*start_routine)(void *),
		void *arg)
{
	if (pthread_create(threadp, NULL, start_routine, arg))
		fatal_error("cannot create %lu thread", (unsigned long)threadp);
}

void	thread_detach(t_thread thread)
{
	if (pthread_detach(thread))
		fatal_error("cannot detach %lu thread", (unsigned long)thread);
}
