/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:49:44 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 07:25:41 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

void		init_philo(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->total_philo)
	{
		state->philo[i].philo_index = i;
		state->philo[i].fork_r = i;
		state->philo[i].fork_l = (i + 1) % state->total_philo;
		state->philo[i].now_eating = 0;
		state->philo[i].eating_count = 0;
		state->philo[i].state = state;
		state->philo[i].must_eat_done = 0;
		pthread_mutex_init(&state->philo[i].check_m, NULL);
		i++;
	}
}

int			init_mutex(t_state *state)
{
	int		i;

	pthread_mutex_init(&state->message_m, NULL);
	pthread_mutex_init(&state->end_m, NULL);
	pthread_mutex_lock(&state->end_m);
	if (!(state->fork_m = malloc(sizeof(pthread_mutex_t) * state->total_philo)))
		return (0);
	i = 0;
	while (i < state->total_philo)
	{
		pthread_mutex_init(&state->fork_m[i], NULL);
		i++;
	}
	return (1);
}

int			init_state(t_state *state, int argc, char **argv)
{
	state->total_philo = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->philo_must_eat_times = ft_atoi(argv[5]);
	else
		state->philo_must_eat_times = -1;
	state->someone_die = 0;
	state->philo = NULL;
	state->fork_m = NULL;
	if (!(state->philo = malloc(sizeof(t_philo) * state->total_philo)))
		return (0);
	if (!(init_mutex(state)))
		return (0);
	init_philo(state);
	return (1);
}
