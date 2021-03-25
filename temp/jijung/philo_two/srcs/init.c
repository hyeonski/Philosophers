/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:54:09 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 08:38:30 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

int			init_philo(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->total_philo)
	{
		state->philo[i].philo_index = i;
		state->philo[i].now_eating = 0;
		state->philo[i].eating_count = 0;
		state->philo[i].state = state;
		state->philo[i].must_eat_done = 0;
		sem_unlink(SEM_CHECK);
		if ((state->philo[i].check_s = sem_open(SEM_CHECK, O_CREAT, 0644, \
			1)) == SEM_FAILED)
			return (0);
		i++;
	}
	return (1);
}

int			init_sema(t_state *state)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MESSAGE);
	sem_unlink(SEM_END);
	sem_unlink(SEM_DIE_MESSAGE);
	if ((state->fork_s = sem_open(SEM_FORK, O_CREAT, 0644, \
		state->total_philo)) == SEM_FAILED)
		return (0);
	if ((state->message_s = sem_open(SEM_MESSAGE, O_CREAT, 0644, \
		1)) == SEM_FAILED)
		return (0);
	if ((state->die_message_s = sem_open(SEM_DIE_MESSAGE, O_CREAT, 0644, \
		1)) == SEM_FAILED)
		return (0);
	if ((state->end_s = sem_open(SEM_END, O_CREAT, 0644, \
		0)) == SEM_FAILED)
		return (0);
	return (1);
}

int			init_state(t_state *state, int argc, char **argv)
{
	state->total_philo = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->must_eat = ft_atoi(argv[5]);
	else
		state->must_eat = -1;
	state->someone_die = 0;
	state->philo = NULL;
	state->fork_s = NULL;
	if (!(state->philo = malloc(sizeof(t_philo) * state->total_philo)))
		return (0);
	if (!(init_sema(state)))
		return (0);
	if (!(init_philo(state)))
		return (0);
	return (1);
}
