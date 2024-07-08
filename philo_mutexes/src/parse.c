/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:02:14 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 17:07:02 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= 0x30 && c <= 0x39);
}

static void	whitespace(char **str)
{
	if (str == 0 || *str == 0)
		return ;
	while (**str == 0x20 || **str == 0xD || **str == 0xA || **str == 0x9)
		(*str)++;
}

static ssize_t	ft_strtoi(const char *nptr, char **endptr)
{
	ssize_t		acc;
	int			neg;
	const char	*s = nptr;

	acc = 0;
	whitespace((char **)&s);
	neg = (*s == '-');
	if (*s == '-' || *s == '+')
		s++;
	if (ft_isdigit(*s) == 0 && endptr != 0)
		return (*endptr = (char *)nptr, acc);
	while (ft_isdigit(*s))
	{
		if (neg && (acc < (INT_MIN + (*s - '0')) / 10))
			return (errno = ERANGE, acc = INT_MIN);
		if (neg == 0 && (acc > (INT_MAX - (*s - '0')) / 10))
			return (errno = ERANGE, acc = INT_MAX);
		if (neg)
			acc = acc * 10 - (*s++ - '0');
		else
			acc = acc * 10 + (*s++ - '0');
	}
	if (endptr != 0)
		*endptr = (char *)s;
	return (acc);
}

static int	legal_number(const char *string, int *result)
{
	ssize_t	value;
	char	*ep;

	if (result)
		*result = 0;
	if (string == 0)
		return (0);
	errno = 0;
	value = ft_strtoi(string, &ep);
	if (errno || ep == string)
		return (0);
	whitespace(&ep);
	if (*string && *ep == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}

int	set_table(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (internal_error("invalid number of arguments"), 1);
	if (legal_number(*(argv + 1), &(*table).num_philos) == 0
		|| (*table).num_philos <= 1)
		return (parser_error("invalid number of philosophers: %s", *(argv + 1)),
			1);
	if (legal_number(*(argv + 2), &(*table).time_die) == 0
		|| (*table).time_die <= 0)
		return (parser_error("invalid time to die: %s", *(argv + 2)), 1);
	if (legal_number(*(argv + 3), &(*table).time_eat) == 0
		|| (*table).time_eat <= 0)
		return (parser_error("invalid time to eat: %s", *(argv + 3)), 1);
	if (legal_number(*(argv + 4), &(*table).time_sleep) == 0
		|| (*table).time_sleep <= 0)
		return (parser_error("invalid time to sleep: %s", *(argv + 4)), 1);
	if (argc == 6 && (legal_number(*(argv + 5), &(*table).num_must_eat) == 0
			|| (*table).num_must_eat <= 0))
		return (parser_error("invalid time of each philosopher must eat: %s",
				*(argv + 5)), 1);
	else
		(*table).num_must_eat = 0;
	(*table).dinner_served = 1;
	return (0);
}
