/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:55:33 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/29 15:57:52 by hyeonski         ###   ########.fr       */
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
		if (philo->cnt_eat == philo->table->num_to_eat)
			break ;
		current_time = get_time();
		if (current_time - philo->last_eat > philo->table->time_to_die)
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
		my_sleep(1);
	}
	return (NULL);
}
