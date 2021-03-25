/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 22:21:27 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 15:35:27 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define EVENT_FORK		0
# define EVENT_EAT		1
# define EVENT_SLEEP	2
# define EVENT_THINK	3
# define EVENT_DIED		4

struct s_env;

typedef struct			s_philo
{
	pthread_t			th_id;
	int					index;
	long				t_last_eat;
	int					n_eaten;
	int					l_fork;
	int					r_fork;
	int					full;
	int					dead;
	struct s_env		*env;
}						t_philo;

typedef struct			s_env
{
	int					n_philo;
	long				t_to_die;
	long				t_to_eat;
	long				t_to_sleep;
	int					n_must_eat;
	int					n_finished;
	int					i;
	long				start;
	t_philo				**p;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		end;
}						t_env;

long					ft_atoi(const char *str);
int						ft_putstr(char const *s);
long					ft_get_time(void);
void					ft_eat(t_philo *philo);
void					ft_sleep_and_think(t_philo *philo);
void					ft_die(t_philo *philo);
void					ft_putnbr_fd(long n, int fd);
int						ft_clear(t_env *env);
int						ft_parse_env(int argc, char **argv, t_env *env);
int						ft_init_philo(t_env *env, int i);
int						ft_init_mutex(t_env *env);
void					ft_put_msg(t_philo *philo, int event_t);
void					ft_my_sleep(long t_sleep);
char					*ft_strjoin(char *s1, char *s2, int free_case);
int						ft_strlen(const char *str);
char					*ft_itoa(long n);
int						ft_putchar(int c);
int						ft_isdigit(int c);
int						ft_isspace(int c);
#endif
