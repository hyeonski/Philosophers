/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:55:53 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 01:56:05 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

int			clean_state(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->total_philo)
	{
		kill(state->philo[i].pid, SIGKILL);
		i++;
	}
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MESSAGE);
	sem_unlink(SEM_END);
	sem_unlink(SEM_CHECK);
	if (state->philo)
	{
		free(state->philo);
		state->philo = NULL;
	}
	return (1);
}

int			exit_error(char *str)
{
	if (str)
		printf("%s\n", str);
	return (1);
}
