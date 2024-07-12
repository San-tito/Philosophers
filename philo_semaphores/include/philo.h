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
# include <fcntl.h>
# include <limits.h>
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

# define SEM_FORKS "/forks"
# define SEM_LOG "/log"
# define SEM_SERVED "/served"

typedef sem_t	t_sem;

typedef enum e_sem_action
{
	WAIT,
	POST
}				t_sem_action;

t_sem			*semaphore_init(const char *name, unsigned int value);
void			semaphore_control(t_sem *sem, t_sem_action action);
void			semaphore_destroy(const char *name, t_sem *sem);
pid_t			make_child(void);
int				waitchld(pid_t pid);
int				process_exit_status(int status);

/* ************************************************************************** */
/*                              Table Structure                               */
/* ************************************************************************** */

typedef struct s_table
{
	int8_t		dinner_served;
	int32_t		num_philos;
	int32_t		time_die;
	int32_t		time_eat;
	int32_t		time_sleep;
	int32_t		num_must_eat;
	time_t		start_time;
	t_sem		*log_sem;
	t_sem		*served_sem;
}				t_table;

/* ************************************************************************** */
/*                            Philosopher Structure                           */
/* ************************************************************************** */

typedef struct s_philo
{
	int32_t		id;
	pid_t		pid;
	t_sem		*forks;
	int32_t		meal_count;
	time_t		last_meal;
	t_table		*table;
}				t_philo;

/* ************************************************************************** */
/*                               Time-related Functions                      */
/* ************************************************************************** */

time_t			current_time(void);
void			sleep_for(int64_t milliseconds, t_table *table);
void			spinlock(time_t start_time);

/* ************************************************************************** */
/*                              Parse Functions                               */
/* ************************************************************************** */

t_table			set_table(int argc, char **argv);

/* ************************************************************************** */
/*                             Error Handling                                 */
/* ************************************************************************** */
void			parser_error(const char *format, const char *arg);
void			fatal_error(const char *format, unsigned long arg);
void			internal_error(const char *format);

/* ************************************************************************** */
/*                           Memory Allocation                                */
/* ************************************************************************** */
void			xfree(void *string);
void			*xmalloc(size_t bytes);

/* ************************************************************************** */
/*                           Philosopher Process Routine                      */
/* ************************************************************************** */
void			philosopher(t_philo *philo, t_table *table);
int				dinner_is_served(t_table *table);

#endif
