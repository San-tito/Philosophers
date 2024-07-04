/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:49:21 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/27 14:52:30 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*xmalloc(size_t bytes)
{
	void	*temp;

	temp = malloc(bytes);
	if (temp == 0)
		fatal_error("xmalloc: cannot allocate %lu bytes", (unsigned long)bytes);
	return (temp);
}

void	xfree(void *string)
{
	if (string)
		free(string);
}
