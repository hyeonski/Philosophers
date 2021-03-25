/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_must_eat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 07:16:55 by jijung            #+#    #+#             */
/*   Updated: 2021/03/05 08:48:00 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int			full_check(t_philo *philo)
{
	if (philo->state->philo_must_eat_times > 0 &&
		philo->eating_count == philo->state->philo_must_eat_times)
	{
		pthread_mutex_lock(&philo->check_m);
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
				pthread_mutex_unlock(&state->end_m);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
