/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinho <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:50:17 by jinho             #+#    #+#             */
/*   Updated: 2021/03/05 08:47:47 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

void		*check_eat_time(void *value)
{
	t_philo			*philo;

	philo = (t_philo *)value;
	while (philo->state->someone_die == 0)
	{
		pthread_mutex_lock(&philo->check_m);
		if (!philo->now_eating && get_cur_time() > philo->limit_time)
		{
			philo->state->someone_die = 1;
			put_message(philo, STATE_DIED);
			pthread_mutex_unlock(&philo->check_m);
			pthread_mutex_unlock(&philo->state->end_m);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->check_m);
		usleep(1000);
	}
	return (NULL);
}

void		*routine(void *philo_c)
{
	t_philo			*philo;
	pthread_t		thread;

	philo = (t_philo *)philo_c;
	philo->last_eat_time = get_cur_time();
	philo->limit_time = philo->last_eat_time + philo->state->time_to_die;
	if (pthread_create(&thread, NULL, &check_eat_time, philo_c) != 0)
		return (NULL);
	pthread_detach(thread);
	if (philo->state->philo_must_eat_times == 0)
	{
		philo->must_eat_done = 1;
		return (NULL);
	}
	while (1)
	{
		hold_forks(philo);
		eating(philo);
		drop_forks(philo);
		if (full_check(philo))
			break ;
		sleep_think(philo);
	}
	return (NULL);
}

int			start_thread(t_state *state)
{
	int				i;
	void			*philo;
	pthread_t		thread;

	state->start_time = get_cur_time();
	if (state->philo_must_eat_times >= 0)
	{
		if (pthread_create(&thread, NULL, &check_must_eat, (void *)state) != 0)
			return (0);
		pthread_detach(thread);
	}
	i = 0;
	while (i < state->total_philo)
	{
		philo = (void *)(&state->philo[i]);
		if (pthread_create(&thread, NULL, &routine, philo) != 0)
			return (0);
		pthread_detach(thread);
		usleep(100);
		i++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_state		state;

	if (!(argu_check(argc, argv)))
		return (EXIT_FAILURE);
	if (!(init_state(&state, argc, argv)))
		return (exit_error("error_init"));
	if (!(start_thread(&state)))
		return (exit_error("error_start_thread"));
	pthread_mutex_lock(&state.end_m);
	clean_state(&state);
	return (0);
}
