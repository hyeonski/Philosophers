/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:48:00 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 05:10:28 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int			clean_state(t_state *state)
{
	int		i;

	if (state->fork_m)
	{
		i = -1;
		while (++i < state->total_philo)
			pthread_mutex_destroy(&state->fork_m[i]);
		free(state->fork_m);
		state->fork_m = NULL;
	}
	pthread_mutex_destroy(&state->message_m);
	pthread_mutex_destroy(&state->end_m);
	if (state->philo)
	{
		i = -1;
		while (++i < state->total_philo)
			pthread_mutex_destroy(&state->philo[i].check_m);
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
