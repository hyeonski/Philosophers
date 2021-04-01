/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:16:26 by hyeonski          #+#    #+#             */
/*   Updated: 2021/04/01 09:27:59 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	eat(t_philo *philo)
{
	t_table		*table;

	table = philo->table;
	sem_wait(table->s_forks);
	put_msg(philo, TAKEN_FORK, get_time());
	sem_wait(table->s_forks);
	put_msg(philo, TAKEN_FORK, get_time());
	put_msg(philo, EATING, get_time());
	my_sleep(philo->table->time_to_eat);
	sem_post(table->s_forks);
	sem_post(table->s_forks);
	++philo->cnt_eat;
	sem_wait(philo->table->s_eat);
	if (philo->table->num_to_eat != -1 && philo->cnt_eat == philo->table->num_to_eat)
	{
		sem_post(philo->table->s_eat);
		return (1);
	}
	sem_post(philo->table->s_eat);
	return (0);
}

void			my_sleep(unsigned long itime)
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

int				is_someone_dead(t_philo *philo, unsigned long curr_time)
{
	if (philo->table->is_dead == TRUE || curr_time - philo->last_eat > philo->table->time_to_die)
		return (1);
	return (0);
}

int				put_msg(t_philo *philo, int status, unsigned long curr_time)
{
	sem_wait(philo->table->s_msg);
	if ((status != DEAD && is_someone_dead(philo, curr_time)))
	{
		sem_post(philo->table->s_msg);
		return (1);
	}
	if (status == TAKEN_FORK)
		printf("%lums %d has taken a fork\n", curr_time - philo->table->base_time, philo->num);
	if (status == EATING)
	{
		printf("%lums %d is eating\n", curr_time - philo->table->base_time, philo->num);
		philo->last_eat = curr_time;
	}
	if (status == SLEEPING && is_someone_dead(philo, curr_time))
		printf("%lums %d is sleeping\n", curr_time - philo->table->base_time, philo->num);
	if (status == THINKING)
		printf("%lums %d is thinking\n", curr_time - philo->table->base_time, philo->num);
	if (status == DEAD)
		printf("%lums %d died\n", curr_time - philo->table->base_time, philo->num);
	sem_post(philo->table->s_msg);
	return (0);	
}

void            *eat_routine(void *philo_ptr)
{
    t_philo     *philo;
    pthread_t   tid;

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
