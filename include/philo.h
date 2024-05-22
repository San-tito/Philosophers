/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:59 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/22 12:46:00 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_params
{
	int		num_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_must_eat;
}			t_params;

int			legal_number(const char *string, int *result);
t_params	parse_arguments(int argc, char **argv);
void		parser_error(const char *format, const char *arg);

#endif
