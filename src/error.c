/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:10:09 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/27 14:54:56 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parser_error(const char *format, const char *arg)
{
	const char	*ename = PROGRAM;

	printf("%s: ", ename);
	if (arg != 0)
		printf(format, arg);
	else
		printf("%s", format);
	printf("\n");
	exit(2);
}

void	fatal_error(const char *format, unsigned long arg)
{
	const char	*ename = PROGRAM;

	printf("%s: ", ename);
	printf(format, arg);
	printf("\n");
	exit(2);
}
