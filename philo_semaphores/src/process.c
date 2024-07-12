/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:26:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 18:06:27 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pid_t	make_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		internal_error("cannot create child process");
	return (pid);
}

int	process_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

int	waitchld(pid_t pid)
{
	int	status;

	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	return (process_exit_status(status));
}
