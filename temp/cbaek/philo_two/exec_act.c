/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_act.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:00:24 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/24 17:11:43 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	eat(t_philo *philo)
{
	t_table		*table;

	table = philo->table;
	sem_wait(table->sm_forks);
	put_msg(philo, TAKEN_FORK, get_time());
	sem_wait(table->sm_forks);
	put_msg(philo, TAKEN_FORK, get_time());
	put_msg(philo, EATING, get_time());
	vsleep(philo->table->time_to_eat);
	sem_post(table->sm_forks);
	sem_post(table->sm_forks);
	philo->cnt_eat += 1;
	sem_wait(table->sm_eat);
	if (philo->table->num_eat != -1 && philo->cnt_eat == philo->table->num_eat)
	{
		sem_post(table->sm_eat);
		return (FAILURE);
	}
	sem_post(table->sm_eat);
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

static int	set_last_meal(t_philo *philo, unsigned long current_time)
{
	philo->last_meal = current_time;
	return (TRUE);
}

int			put_msg(t_philo *philo, int msg, unsigned long current_time)
{
	t_table			*table;

	table = philo->table;
	sem_wait(table->sm_msg);
	if ((msg != DEAD && is_someone_dead(philo, current_time)))
	{
		sem_post(table->sm_msg);
		return (FAILURE);
	}
	(msg == TAKEN_FORK) && printf("%lu %d has taken a fork\n", \
			current_time - table->base_time, philo->nbr);
	(msg == EATING && set_last_meal(philo, current_time)) && printf(\
			"%lu %d is eating\n", current_time - table->base_time, philo->nbr);
	(msg == SLEEPING) && printf("%lu %d is sleeping\n", \
			current_time - table->base_time, philo->nbr);
	(msg == THINKING) && printf("%lu %d is thinking\n", \
			current_time - table->base_time, philo->nbr);
	(msg == DEAD) && printf("%lu %d died\n", \
			current_time - table->base_time, philo->nbr);
	sem_post(table->sm_msg);
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
