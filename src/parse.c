/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/21 20:22:47 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= 0x30 && c <= 0x39);
}

static int	ft_isspace(int c)
{
	return (c == 0x20 || c == 0xD || c == 0xA || c == 0x9);
}

ssize_t	ft_strtoi(const char *s)
{
	ssize_t	acc;
	int		neg;

	while (ft_isspace(*s))
		s++;
	neg = 0;
	if (*s == '-')
		neg = 1;
	if (*s == '-' || *s == '+')
		s++;
	acc = 0;
	while (ft_isdigit(*s))
	{
		if ((neg && (acc < (INT_MIN + (*s - '0')) / 10)) || (neg == 0
				&& (acc > (INT_MAX - (*s - '0')) / 10)))
			return (errno = ERANGE);
		if (neg)
			acc = acc * 10 - (*s - '0');
		else
			acc = acc * 10 + (*s - '0');
		s++;
	}
	return (acc);
}

int	legal_number(const char *string, int *result)
{
	ssize_t	value;

	if (result)
		*result = 0;
	if (string == 0 || *string == '\0')
		return (0);
	errno = 0;
	value = ft_strtoi(string);
	if (errno)
		return (0);
	while (ft_isspace(*string))
		string++;
	if (*string == '-' || *string == '+')
		string++;
	if (*string == '\0')
		return (0);
	while (ft_isdigit(*string))
		string++;
	if (*string == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}
