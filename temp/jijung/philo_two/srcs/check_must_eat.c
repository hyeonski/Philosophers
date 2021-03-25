/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_must_eat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:53:58 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 08:38:13 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

int			full_check(t_philo *philo)
{
	if (philo->state->must_eat > 0 &&
		philo->eating_count == philo->state->must_eat)
	{
		sem_wait(philo->check_s);
		philo->must_eat_done = 1;
		return (1);
	}
	return (0);
}

void		*check_must_eat(void *state_c)
{
	t_state			*state;
	int				i;

	state = (t_state *)state_c;
	while (state->someone_die == 0)
	{
		i = 0;
		while (i < state->total_philo)
		{
			if (state->philo[i].must_eat_done == 0)
				break ;
			if (i == state->total_philo - 1)
			{
				put_message(&state->philo[0], STATE_END);
				sem_post(state->end_s);
				return (NULL);
			}
			i++;
		}
	}
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
