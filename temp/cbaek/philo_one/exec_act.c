/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_act.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:43:12 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/29 15:40:44 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	eat(t_philo *philo)
{
	t_table		*table;

	table = philo->table;
	pthread_mutex_lock(&table->m_forks[philo->fork1]);
	put_msg(philo, TAKEN_FORK, get_time());
	pthread_mutex_lock(&table->m_forks[philo->fork2]);
	put_msg(philo, TAKEN_FORK, get_time());
	put_msg(philo, EATING, get_time());
	vsleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&table->m_forks[philo->fork1]);
	pthread_mutex_unlock(&table->m_forks[philo->fork2]);
	philo->cnt_eat += 1;
	pthread_mutex_lock(&philo->table->m_eat);
	if (philo->table->num_eat != -1 && philo->cnt_eat == philo->table->num_eat)
	{
		pthread_mutex_unlock(&philo->table->m_eat);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (SUCCESS);
}

static int	is_someone_dead(t_philo *philo, unsigned long current_time)
{
	int	ret;

	ret = FALSE;
	if (philo->table->is_dead == TRUE ||
		current_time - philo->last_meal > philo->table->time_to_die)
		ret = TRUE;
	return (ret);
}

int			put_msg(t_philo *philo, int msg, unsigned long current_time)
{
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&table->m_msg);
	if ((msg != DEAD && is_someone_dead(philo, current_time)))
	{
		pthread_mutex_unlock(&table->m_msg);
		return (FAILURE);
	}
	printf("%lu %d", current_time - philo->table->base_time, philo->nbr);
	(msg == TAKEN_FORK) && printf(" has taken a fork\n");
	if (msg == EATING)
	{
		printf(" is eating\n");
		philo->last_meal = current_time;
	}
	(msg == SLEEPING) && printf(" is sleeping\n");
	(msg == THINKING) && printf(" is thinking\n");
	(msg == DEAD) && printf(" died\n");
	pthread_mutex_unlock(&table->m_msg);
	return (SUCCESS);
}

void		*exec_act(void *void_philo)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)void_philo;
	if (philo->nbr % 2 == 0)
		vsleep(1);
	pthread_create(&tid, NULL, philo_monitor, philo);
	while (TRUE)
	{
		if (eat(philo))
			break ;
		if (put_msg(philo, SLEEPING, get_time()))
			break ;
		vsleep(philo->table->time_to_sleep);
		if (put_msg(philo, THINKING, get_time()))
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
