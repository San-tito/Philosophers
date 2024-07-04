/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:59 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 18:02:14 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PROGRAM "philo"

/* ************************************************************************** */
/*                               Time-related Functions                      */
/* ************************************************************************** */
time_t	current_time(void);
void	sleep_for(int64_t milliseconds, int8_t flag);

/* ************************************************************************** */
/*                              Parse Functions                               */
/* ************************************************************************** */
t_table	parse_arguments(int argc, char **argv);

/* ************************************************************************** */
/*                             Error Handling                                 */
/* ************************************************************************** */
void	parser_error(const char *format, const char *arg);
void	fatal_error(const char *format, unsigned long arg);
void	internal_error(const char *format);

/* ************************************************************************** */
/*                           Memory Allocation                                */
/* ************************************************************************** */
void	xfree(void *string);
void	*xmalloc(size_t bytes);

/* ************************************************************************** */
/*                           Philosopher Thread Routine                       */
/* ************************************************************************** */
void	*philosopher(void *arg);

#endif
