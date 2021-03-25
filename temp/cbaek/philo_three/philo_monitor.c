/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:03:17 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/25 11:06:50 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
				put_msg(philo, DEAD, current_time);
				exit(EXIT_FAILURE);
			}
			sem_post(philo->table->sm_dead);
			return (NULL);
		}
		vsleep(1);
	}
	return (NULL);
}
