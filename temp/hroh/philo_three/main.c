/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 22:17:59 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 23:54:46 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*ft_dead_monitor(void *p)
{
	t_philo		*philo;
	long		now;
	int			i;

	philo = (t_philo*)p;
	while (philo->dead == 0 && philo->full == 0)
	{
		now = ft_get_time();
		i = 0;
		if (now - philo->t_last_eat > philo->env->t_to_die)
		{
			ft_die(philo);
			sem_wait(philo->env->print_sem);
			sem_post(philo->env->end_sem);
			i = -1;
			while (++i < philo->env->n_philo)
				philo->env->p[i]->dead = 1;
			return (0);
		}
		usleep(1000);
	}
	return (0);
}

int		ft_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	th_id;

	philo = (t_philo *)arg;
	if (pthread_create(&th_id, NULL, &ft_dead_monitor, (void *)philo) != 0)
		return (ft_putstr("Error : pthread_create error\n"));
	pthread_detach(th_id);
	if (pthread_create(&th_id, NULL, &ft_full_wait, (void *)philo) != 0)
		return (ft_putstr("Error : pthread_create error\n"));
	pthread_detach(th_id);
	while (philo->dead == 0 && philo->full == 0)
	{
		ft_eat(philo);
		if (philo->env->n_must_eat > 0 &&
			philo->n_eaten == philo->env->n_must_eat)
		{
			philo->full = 1;
			break ;
		}
		ft_sleep_and_think(philo);
	}
	if (philo->full == 1)
		sem_post(philo->env->full_sem);
	ft_my_sleep(100);
	return (0);
}

int		ft_make_thread(t_env *env)
{
	int i;

	i = -1;
	env->start = ft_get_time();
	while (++i < env->n_philo)
	{
		if (ft_init_philo(env, i))
			return (ft_putstr("Error : malloc\n"));
		env->i = i;
		if ((env->p[i]->pid = fork()) < 0)
			return (ft_putstr("Error : fork\n"));
		if (env->p[i]->pid == 0)
		{
			ft_routine((void *)env->p[i]);
			exit(0);
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_env		*env;
	pthread_t	th_id;

	if (argc < 5 || argc > 6)
		return (ft_putstr("Error : only 4 or 5 arguments\n"));
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (ft_putstr("Error : malloc\n"));
	if (ft_parse_env(argc, argv, env))
		return (ft_putstr("Error : Invalid arguments\n"));
	if (!(env->p = (t_philo **)malloc(sizeof(t_philo *) * env->n_philo)))
		return (ft_putstr("Error : malloc\n"));
	if (ft_init_mutex(env))
		return (ft_clear(env) && ft_putstr("Error : malloc\n"));
	ft_make_thread(env);
	if (pthread_create(&th_id, NULL, &ft_full_end, (void *)env) != 0)
		return (ft_clear(env) && ft_putstr("Error : pthread_create error\n"));
	pthread_detach(th_id);
	sem_wait(env->end_sem);
	return (ft_clear(env));
}
