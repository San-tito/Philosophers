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
/*                              Thread and Mutex                              */
/* ************************************************************************** */

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef enum e_mutex_action
{
	LOCK,
	UNLOCK
}						t_mutex_action;

int						thread_mutex_init(t_mutex *mutexp);
int						thread_mutex_control(t_mutex *mutexp,
							t_mutex_action action);
int						thread_mutex_destroy(t_mutex *mutexp);
int						thread_create(t_thread *threadp,
							void *(*start_routine)(void *), void *arg);
int						thread_join(t_thread thread);

/* ************************************************************************** */
/*                              Table Structure                               */
/* ************************************************************************** */

typedef struct s_table
{
	int8_t				dinner_served;
	int32_t				num_philos;
	int32_t				time_die;
	int32_t				time_eat;
	int32_t				time_sleep;
	int32_t				num_must_eat;
	time_t				start_time;
	t_mutex				log_lock;
	t_mutex				served_lock;
	t_thread			waiter_thread;
}						t_table;

/* ************************************************************************** */
/*                            Philosopher Structure                           */
/* ************************************************************************** */

typedef struct s_philo
{
	int32_t				id;
	t_thread			thread;
	t_mutex				*first_fork;
	t_mutex				*second_fork;
	t_mutex				meal_lock;
	int32_t				meal_count;
	time_t				last_meal;
	t_table				*table;
}						t_philo;

/* ************************************************************************** */
/*                               Time-related Functions                      */
/* ************************************************************************** */

time_t					current_time(void);
void					sleep_for(int64_t milliseconds, int8_t flag);

/* ************************************************************************** */
/*                              Parse Functions                               */
/* ************************************************************************** */

int						set_table(int argc, char **argv, t_table *table);

/* ************************************************************************** */
/*                             Error Handling                                 */
/* ************************************************************************** */

void					parser_error(const char *format, const char *arg);
void					fatal_error(const char *format, unsigned long arg);
void					internal_error(const char *format);

/* ************************************************************************** */
/*                           Memory Allocation                                */
/* ************************************************************************** */

void					xfree(void *string);
void					*xmalloc(size_t bytes);

/* ************************************************************************** */
/*                           Philosopher Thread Routine                       */
/* ************************************************************************** */

void					*philosopher(void *arg);
void					*waiter(void *arg);
int						dinner_is_served(t_table *table);
void					log_state(const char *state, t_philo *philo,
							t_table *table);

#endif
