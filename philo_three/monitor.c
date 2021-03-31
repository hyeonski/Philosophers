/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:15:39 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/31 21:23:01 by hyeonski         ###   ########.fr       */
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
				exit(1);
			}
			sem_post(philo->table->s_dead);
			return (NULL);
		}
		my_sleep(1);
	}
	return (NULL);
}

static void	kill_child(t_philo *philos)
{
	int		idx;

	idx = 0;
	while (idx < philos->table->num_of_philos)
	{
		kill(philos[idx].pid, SIGKILL);
		idx++;
	}
	// sem_post(philos->table->s_msg);
}

void		process_monitor(t_philo *philos)
{
	int	status;
	int	full;
	int	i;
	
	full = 0;
	while (1)
	{
		i = 0;
		while (i < philos->table->num_of_philos)
		{
			status = -1;
			waitpid(philos[i].pid, &status, WNOHANG);
			if (status == 0)
				full++;
			if ((status / 256) == 1 || full == philos->table->num_of_philos)
				break ;
			i++;
		}
		if ((status / 256) == 1 || full == philos->table->num_of_philos)
		{
			kill_child(philos);
			break ;
		}
	}
}