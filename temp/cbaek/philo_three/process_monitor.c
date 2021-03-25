/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:47:14 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/25 12:31:46 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	kill_process(t_philo *philos)
{
	int		idx;

	idx = 0;
	while (idx < philos->table->num_of_philos)
	{
		kill(philos[idx].pid, SIGKILL);
		idx++;
	}
	sem_post(philos->table->sm_msg);
	return (TRUE);
}

void		process_monitor(t_philo *philos)
{
	int		idx;
	int		status;
	int		fully_eat;

	fully_eat = 0;
	while (TRUE)
	{
		idx = 0;
		while (idx < philos->table->num_of_philos)
		{
			status = -1;
			waitpid(philos[idx].pid, &status, WNOHANG);
			if (status == 0)
				fully_eat++;
			if (status == 256 || fully_eat == philos->table->num_of_philos)
				break ;
			idx++;
		}
		if ((status == 256 || fully_eat == philos->table->num_of_philos) && \
				kill_process(philos) == 1)
			break ;
	}
}
