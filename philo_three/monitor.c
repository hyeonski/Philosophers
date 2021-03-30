/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:15:39 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/30 20:16:02 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*philo_monitor(void *void_philo)
{
	t_philo			*philo;
	unsigned long	curr_time;

	philo = (t_philo *)void_philo;
	while (TRUE)
	{
		if (philo->cnt_eat == philo->table->num_to_eat)
			break ;
		curr_time = get_time();
		if (curr_time - philo->last_eat > philo->table->time_to_die)
		{
			sem_wait(philo->table->s_dead);
			if (philo->table->is_dead == FALSE)
			{
				philo->table->is_dead = TRUE;
				sem_post(philo->table->s_forks);
				put_msg(philo, DEAD, curr_time);
			}
			sem_post(philo->table->s_dead);
			return (NULL);
		}
		my_sleep(1);
	}
	return (NULL);
}
