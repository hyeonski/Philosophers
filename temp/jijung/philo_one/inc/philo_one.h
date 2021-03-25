/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:47:25 by jijung            #+#    #+#             */
/*   Updated: 2021/03/05 08:48:53 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define STATE_FORK		0
# define STATE_EAT		1
# define STATE_SLEEP	2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_END		5

struct s_state;

typedef struct			s_philo
{
	struct s_state		*state;
	int					philo_index;
	int					fork_l;
	int					fork_r;
	int					now_eating;
	int					eating_count;
	uint64_t			last_eat_time;
	uint64_t			limit_time;
	int					must_eat_done;
	pthread_mutex_t		check_m;
}						t_philo;

typedef struct			s_state
{
	int					total_philo;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int					philo_must_eat_times;
	t_philo				*philo;
	uint64_t			start_time;
	int					someone_die;
	pthread_mutex_t		message_m;
	pthread_mutex_t		*fork_m;
	pthread_mutex_t		end_m;
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
void					init_philo(t_state *state);
int						init_mutex(t_state *state);
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
int						full_check(t_philo *philo);
void					*check_must_eat(void *state_c);

/*
** main
*/
void					*check_eat_time(void *value);
void					*routine(void *philo_c);
int						start_thread(t_state *state);
int						main(int argc, char **argv);

#endif
