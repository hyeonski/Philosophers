/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 19:04:16 by hyeonski          #+#    #+#             */
/*   Updated: 2021/04/01 10:10:23 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

# define TRUE		1
# define FALSE		0

# define TAKEN_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

typedef struct		s_table
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_to_eat;
	unsigned long	base_time;
	int				is_dead;
	sem_t			*s_forks;
	sem_t			*s_msg;
	sem_t			*s_eat;
	sem_t			*s_dead;
}					t_table;

typedef struct		s_philo
{
	t_table			*table;
	int				num;
	int				cnt_eat;
	unsigned long	last_eat;
	pid_t			pid;
}					t_philo;

int					put_msg(t_philo *philo, int msg,
		unsigned long current_time);
void				*eat_routine(void *void_philo);
void				*philo_monitor(void *void_philo);
void				process_monitor(t_philo *philos);
int					ft_atoi(const char *str);
int					p_error(char *str);
unsigned long		get_time(void);
int					parse_num_arg(char *str);
void				my_sleep(unsigned long itime);
void				unlink_sems(void);

#endif
