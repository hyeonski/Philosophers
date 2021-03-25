/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:54:03 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 03:42:25 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

int			clean_state(t_state *state)
{
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
