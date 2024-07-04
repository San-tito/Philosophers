/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:10:09 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/28 12:29:18 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parser_error(const char *format, const char *arg)
{
	const char	*ename = PROGRAM;

	printf("%s: ", ename);
	printf(format, arg);
	printf("\n");
}

void	internal_error(const char *format)
{
	const char	*ename = PROGRAM;

	printf("%s: ", ename);
	printf("%s", format);
	printf("\n");
}

void	fatal_error(const char *format, unsigned long arg)
{
	const char	*ename = PROGRAM;

	printf("%s: ", ename);
	printf(format, arg);
	printf("\n");
}
