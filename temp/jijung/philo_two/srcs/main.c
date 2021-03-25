/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:54:20 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 08:52:10 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

void		*check_time(void *value)
{
	t_philo			*philo;

	philo = (t_philo *)value;
	while (philo->state->someone_die == 0)
	{
		sem_wait(philo->check_s);
		if (!philo->now_eating && get_cur_time() > philo->limit_time)
		{
			philo->state->someone_die = 1;
			put_message(philo, STATE_DIED);
			sem_post(philo->check_s);
			sem_post(philo->state->end_s);
			return (NULL);
		}
		sem_post(philo->check_s);
		usleep(1000);
	}
	return (NULL);
}

void		*routine(void *philo_c)
{
	t_philo			*philo;
	pthread_t		thread;

	philo = (t_philo *)philo_c;
	philo->last_eat = get_cur_time();
	philo->limit_time = philo->last_eat + philo->state->time_to_die;
	if (pthread_create(&thread, NULL, &check_time, philo_c) != 0)
		return (NULL);
	pthread_detach(thread);
	if (philo->state->must_eat == 0)
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
	if (!(create_check_must_eat(&state)))
		return (exit_error("error_check_must_eat"));
	if (!(start_thread(&state)))
		return (exit_error("error_start_thread"));
	sem_wait(state.end_s);
	clean_state(&state);
	return (EXIT_SUCCESS);
}
