/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:57:41 by hyeonski          #+#    #+#             */
/*   Updated: 2021/04/01 09:27:15 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int			eat(t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&table->m_forks[philo->fork1]);
	put_msg(philo, TAKEN_FORK, get_time());
	pthread_mutex_lock(&table->m_forks[philo->fork2]);
	put_msg(philo, TAKEN_FORK, get_time());
	put_msg(philo, EATING, get_time());
	my_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&table->m_forks[philo->fork1]);
	pthread_mutex_unlock(&table->m_forks[philo->fork2]);
	++philo->cnt_eat;
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->table->num_to_eat != -1
			&& philo->cnt_eat == philo->table->num_to_eat)
	{
		pthread_mutex_unlock(&philo->table->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (0);
}

void				my_sleep(unsigned long itime)
{
	unsigned long	stime;
	unsigned long	ctime;

	stime = get_time();
	while (1)
	{
		ctime = get_time();
		if (ctime - stime > itime)
			return ;
		usleep(100);
	}
}

int					is_someone_dead(t_philo *philo, unsigned long curr_time)
{
	if (philo->table->is_dead == TRUE
			|| curr_time - philo->last_eat > philo->table->time_to_die)
		return (1);
	return (0);
}

int					put_msg(t_philo *philo, int status, unsigned long curr_time)
{
	pthread_mutex_lock(&(philo->table->m_msg));
	if ((status != DEAD && is_someone_dead(philo, curr_time)))
	{
		pthread_mutex_unlock(&(philo->table->m_msg));
		return (1);
	}
	printf("%lums %d", curr_time - philo->table->base_time, philo->num);
	if (status == TAKEN_FORK)
		printf(" has taken a fork\n");
	if (status == EATING)
	{
		printf(" is eating\n");
		philo->last_eat = curr_time;
	}
	if (status == SLEEPING)
		printf(" is sleeping\n");
	if (status == THINKING)
		printf(" is thinking\n");
	if (status == DEAD)
		printf(" died\n");
	pthread_mutex_unlock(&(philo->table->m_msg));
	return (0);
}

void				*eat_routine(void *philo_ptr)
{
	t_philo			*philo;
	pthread_t		tid;

	philo = (t_philo *)philo_ptr;
	if (philo->num % 2 == 0)
		my_sleep(philo->table->time_to_eat - 1);
	pthread_create(&tid, NULL, philo_monitor, philo);
	while (1)
	{
		if (eat(philo))
			break ;
		if (put_msg(philo, SLEEPING, get_time()))
			break ;
		my_sleep(philo->table->time_to_sleep);
		if (put_msg(philo, THINKING, get_time()))
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
