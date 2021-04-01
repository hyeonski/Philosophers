/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:49:45 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/29 18:42:57 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

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
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_msg;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}					t_table;

typedef struct		s_philo
{
	t_table			*table;
	int				fork1;
	int				fork2;
	int				num;
	int				cnt_eat;
	unsigned long	last_eat;
	pthread_t		tid;
}					t_philo;

int					put_msg(t_philo *philo, int msg,
		unsigned long current_time);
void				*eat_routine(void *void_philo);
void				*philo_monitor(void *void_philo);
int					ft_atoi(const char *str);
int					p_error(char *str);
unsigned long		get_time(void);
void				my_sleep(unsigned long itime);
int					parse_num_arg(char *str);

#endif
