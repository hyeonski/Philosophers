/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:41:04 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/23 16:54:29 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_monitor(void *void_philo)
{
	t_philo			*philo;
	unsigned long	current_time;

	philo = (t_philo *)void_philo;
	while (TRUE)
	{
		if (philo->cnt_eat == philo->table->num_eat)
			break ;
		current_time = get_time();
		if (current_time - philo->last_meal > philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->table->m_dead);
			if (philo->table->is_dead == FALSE)
			{
				philo->table->is_dead = TRUE;
				pthread_mutex_unlock(&philo->table->m_forks[philo->fork1]);
				put_msg(philo, DEAD, current_time);
			}
			pthread_mutex_unlock(&philo->table->m_dead);
			return (NULL);
		}
		vsleep(1);
	}
	return (NULL);
}
