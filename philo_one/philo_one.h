/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:26:32 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/25 16:42:03 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define TAKEN_FORK	0
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define DEAD		4

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct		s_table
{
	int				num_of_philos;
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				tot_eat;
	int				is_dead;
	unsigned long	base_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_msg;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}					t_table;

typedef struct		s_philo
{
	int				nbr;
	int				fork1;
	int				fork2;
	int				cnt_eat;
	unsigned long	last_meal;
	pthread_t		tid;
	t_table			*table;
}					t_philo;

int					parse(t_table *table, char **argv);
int					init_table(t_table *table, t_philo *philos);
void				init_philo(t_philo *philos);
void				*philo_act(void *phi);
void				*philo_monitor(void *phi);
int					eat(t_philo *philo);
int					msg(t_philo *philo, int msg, unsigned long current_time);
int					someone_dead(t_philo *philo, unsigned long current_time);
int					fully_eat(t_philo *philo);
int					ft_atoi(const char *str);
unsigned long		get_time(void);
void				vsleep(unsigned long itime);
void				clean_table(t_table *table, t_philo *philos);
int					p_error(char *str);

#endif