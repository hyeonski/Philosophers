/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:01:07 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/25 10:49:37 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

/*
** headers
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

/*
** macro
*/

# define TRUE		1
# define FALSE		0
# define FAILURE	1
# define SUCCESS	0
# define U_DELAY	50

/*
** enum
*/

typedef enum		e_status
{
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}					t_status;

/*
** struct
*/

typedef struct		s_table
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	base_time;
	int				num_of_philos;
	int				num_eat;
	int				is_dead;
	sem_t			*sm_forks;
	sem_t			*sm_msg;
	sem_t			*sm_eat;
	sem_t			*sm_dead;
}					t_table;

typedef struct		s_philo
{
	t_table			*table;
	int				nbr;
	int				cnt_eat;
	unsigned long	last_meal;
	pid_t			pid;
}					t_philo;

/*
** function
*/

void				process_monitor(t_philo *philos);
int					put_msg(t_philo *philo, int msg, \
							unsigned long current_time);
void				*exec_act(void *void_philo);
void				*philo_monitor(void *void_philo);
int					ft_atoi(const char *str);
int					put_error(const char *str);
unsigned long		get_time(void);
void				vsleep(unsigned long itime);

#endif
