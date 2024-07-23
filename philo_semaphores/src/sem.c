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

t_sem	*semaphore_init(const char *name, unsigned int value)
{
	t_sem	*sem;

	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
		parser_error("cannot initialize semaphore %s", name);
	if (sem_unlink(name) < 0)
		parser_error("cannot unlink semaphore %s", name);
	return (sem);
}

void	semaphore_control(t_sem *sem, t_sem_action action)
{
	if (action == WAIT)
	{
		if (sem_wait(sem) < 0)
			fatal_error("cannot wait on semaphore %lu", (unsigned long)sem);
	}
	else if (action == POST)
	{
		if (sem_post(sem) < 0)
			fatal_error("cannot post semaphore %lu", (unsigned long)sem);
	}
}

void	semaphore_destroy(t_sem *sem)
{
	if (sem_close(sem) < 0)
		fatal_error("cannot close semaphore %lu", (unsigned long)sem);
}
