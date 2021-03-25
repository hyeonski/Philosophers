/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_must_eat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:55:48 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 09:54:11 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

int			full_check(t_philo *philo)
{
	if (philo->state->must_eat > 0 &&
		philo->eating_count == philo->state->must_eat)
	{
		sem_post(philo->state->eat_s);
		sem_wait(philo->check_s);
		return (1);
	}
	return (0);
}

void		*check_must_eat(void *value)
{
	t_state			*state;
	int				i;

	state = (t_state *)value;
	i = 0;
	while (i < state->total_philo)
	{
		sem_wait(state->eat_s);
		i++;
	}
	if (state->someone_die == 1)
		return (NULL);
	put_message(state->philo, STATE_END);
	sem_post(state->end_s);
	return (NULL);
}

int			create_check_must_eat(t_state *state)
{
	pthread_t		thread;

	if (state->must_eat >= 0)
	{
		if (pthread_create(&thread, NULL, &check_must_eat, (void *)state) != 0)
			return (0);
		pthread_detach(thread);
	}
	return (1);
}
