/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:55:31 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 04:31:16 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define STATE_FORK			0
# define STATE_EAT			1
# define STATE_SLEEP		2
# define STATE_THINK		3
# define STATE_DIED			4
# define STATE_END			5

# define SEM_FORK			"sem_fork"
# define SEM_END			"sem_end"
# define SEM_MESSAGE		"sem_message"
# define SEM_EAT			"sem_eat"
# define SEM_CHECK			"sem_check"
# define SEM_DIE_MESSAGE	"sem_die_message"

struct s_state;

typedef struct			s_philo
{
	struct s_state		*state;
	pid_t				pid;
	int					philo_index;
	int					now_eating;
	int					eating_count;
	uint64_t			last_eat;
	uint64_t			limit_time;
	sem_t				*check_s;
}						t_philo;

typedef struct			s_state
{
	int					total_philo;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int					must_eat;
	t_philo				*philo;
	uint64_t			start_time;
	int					someone_die;
	sem_t				*message_s;
	sem_t				*die_message_s;
	sem_t				*fork_s;
	sem_t				*end_s;
	sem_t				*eat_s;
}						t_state;

/*
** utils
*/
int						ft_str_isdigit(char *str);
int						ft_atoi(const char *str);
uint64_t				get_cur_time(void);
void					new_sleep(uint64_t wait_time);

/*
** argu_check
*/
int						argu_input_check(int argc, char **argv);
int						argu_check(int argc, char **argv);

/*
** init
*/
int						init_philo(t_state *state);
int						init_sema(t_state *state);
int						init_state(t_state *state, int argc, char **argv);

/*
** behavior
*/
void					hold_forks(t_philo *philo);
void					eating(t_philo *philo);
void					drop_forks(t_philo *philo);
void					sleep_think(t_philo *philo);

/*
** message
*/
void					put_message(t_philo *philo, int state);
char					*choose_message(int state);

/*
** clean
*/
int						clean_state(t_state *state);
int						exit_error(char *str);

/*
** check_must_eat
*/
int						create_check_must_eat(t_state *state);
void					*check_must_eat(void *value);
int						full_check(t_philo *philo);

/*
** main
*/
int						main(int argc, char **argv);
void					*check_time(void *value);
void					*routine(void *philo_c);
void					*check_eat(void *value);

#endif
