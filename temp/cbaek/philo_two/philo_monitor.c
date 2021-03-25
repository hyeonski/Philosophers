/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:01:02 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/24 17:08:13 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
			sem_wait(philo->table->sm_dead);
			if (philo->table->is_dead == FALSE)
			{
				philo->table->is_dead = TRUE;
				sem_post(philo->table->sm_forks);
				put_msg(philo, DEAD, current_time);
			}
			sem_post(philo->table->sm_dead);
			return (NULL);
		}
		vsleep(1);
	}
	return (NULL);
}
