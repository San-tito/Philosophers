/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:59 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/02 22:33:52 by sguzman          ###   ########.fr       */
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

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_fork;
typedef pthread_mutex_t	t_micro;

typedef struct s_table
{
	int32_t				num_philos;
	int32_t				time_die;
	int32_t				time_eat;
	int32_t				time_sleep;
	int32_t				num_must_eat;
	int64_t				start_time;
	t_micro				micro;
}						t_table;

typedef struct s_philo
{
	int32_t				id;
	t_thread			thread;
	t_table				*table;
	t_fork				*left_fork;
	t_fork				*right_fork;
}						t_philo;

t_table					parse_arguments(int argc, char **argv);
void					parser_error(const char *format, const char *arg);

void					xfree(void *string);
void					*xmalloc(size_t bytes);
void					fatal_error(const char *format, unsigned long arg);

void					*philosopher(void *arg);
void					internal_error(const char *format);

size_t					get_current_time(void);
void					log_state(const t_philo *philosopher);

#endif
