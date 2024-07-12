/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 18:06:27 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_sem	*semaphore_init(const char *name, unsigned int value)
{
	t_sem	*sem;

	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
		parser_error("cannot initialize semaphore %s", name);
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

void	semaphore_destroy(const char *name, t_sem *sem)
{
	if (sem_close(sem) < 0)
		parser_error("cannot close semaphore %s", name);
	if (sem_unlink(name) == -1)
		parser_error("cannot unlink semaphore %s", name);
}
