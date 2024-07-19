/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/18 16:35:47 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_sem	*semaphore_init(t_sem *sem, unsigned int value)
{
	if (sem_init(sem, 1, value))
		fatal_error("cannot initialize semaphore %lu", (unsigned long)sem);
	return (sem);
}

void	semaphore_control(t_sem *sem, t_sem_action action)
{
	int	status;

	if (action == WAIT)
	{
		status = sem_wait(sem);
		if (status < 0)
			fatal_error("cannot wait on semaphore %lu", (unsigned long)sem);
	}
	else if (action == POST)
	{
		status = sem_post(sem);
		if (status < 0)
			fatal_error("cannot post semaphore %lu", (unsigned long)sem);
	}
}

void	semaphore_destroy(t_sem *sem)
{
	if (sem_destroy(sem) < 0)
		fatal_error("cannot destroy semaphore %lu", (unsigned long)sem);
}
