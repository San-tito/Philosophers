/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:59 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/28 13:41:07 by sguzman          ###   ########.fr       */
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

typedef enum e_state
{
	FORK_TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}						t_state;

typedef struct s_params
{
	int					num_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
}						t_params;

typedef pthread_mutex_t	t_fork;

typedef struct s_philo
{
	int					id;
	t_state				state;
	pthread_t			thread;
	t_params			params;
	t_fork				*left_fork;
	t_fork				*right_fork;
}						t_philo;

int						legal_number(const char *string, int *result);
t_params				parse_arguments(int argc, char **argv);
void					parser_error(const char *format, const char *arg);

void					xfree(void *string);
void					*xmalloc(size_t bytes);
void					fatal_error(const char *format, unsigned long arg);

void					*philosopher(void *arg);
void					internal_error(const char *format);

size_t					get_current_time(void);
void					log_state(const t_philo *philosopher);

#endif
