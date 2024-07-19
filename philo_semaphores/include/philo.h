/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:59 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/19 18:04:27 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROGRAM "philo"

/* ************************************************************************** */
/*                              Process and Semaphore                         */
/* ************************************************************************** */

typedef sem_t		t_sem;

typedef enum e_sem_action
{
	WAIT,
	POST
}					t_sem_action;

t_sem				*semaphore_init(t_sem *sem, unsigned int value);
void				semaphore_control(t_sem *sem, t_sem_action action);
void				semaphore_destroy(t_sem *sem);

typedef pthread_t	t_thread;

void				thread_create(t_thread *threadp,
						void *(*start_routine)(void *), void *arg);
void				thread_detach(t_thread thread);

/* ************************************************************************** */
/*                              Table Structure                               */
/* ************************************************************************** */

typedef struct s_table
{
	int8_t			dinner_served;
	int32_t			num_philos;
	int32_t			time_die;
	int32_t			time_eat;
	int32_t			time_sleep;
	int32_t			num_must_eat;
	time_t			start_time;
	t_sem			served_sem;
	t_sem			log_sem;
}					t_table;

/* ************************************************************************** */
/*                            Philosopher Structure                           */
/* ************************************************************************** */

typedef struct s_philo
{
	int32_t			id;
	pid_t			pid;
	t_sem			*first_fork;
	t_sem			*second_fork;
	t_sem			meal_sem;
	int32_t			meal_count;
	time_t			last_meal;
	t_table			*table;
}					t_philo;

/* ************************************************************************** */
/*                               Time-related Functions                      */
/* ************************************************************************** */

time_t				current_time(void);
void				sleep_for(int64_t milliseconds, t_table *table);
void				spinlock(time_t start_time);

/* ************************************************************************** */
/*                              Parse Functions                               */
/* ************************************************************************** */

t_table				set_table(int argc, char **argv);

/* ************************************************************************** */
/*                             Error Handling                                 */
/* ************************************************************************** */
void				parser_error(const char *format, const char *arg);
void				fatal_error(const char *format, unsigned long arg);
void				internal_error(const char *format);

/* ************************************************************************** */
/*                           Memory Allocation                                */
/* ************************************************************************** */
void				xfree(void *string);
void				*xmalloc(size_t bytes);

/* ************************************************************************** */
/*                           Philosopher Process Routine                      */
/* ************************************************************************** */
void				philosopher(t_philo *philo, t_table *table);
void				*arbitrator(void *arg);
int					dinner_is_served(t_table *table);
void				log_state(const char *state, t_philo *philo,
						t_table *table);

#endif
