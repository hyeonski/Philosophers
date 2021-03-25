/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:50:47 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 03:38:32 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

char		*choose_message(int state)
{
	if (state == STATE_FORK)
		return (" has taken a \x1b[32mfork\x1b[0m");
	else if (state == STATE_EAT)
		return (" is \x1b[33meating\x1b[0m");
	else if (state == STATE_SLEEP)
		return (" is \x1b[34msleeping\x1b[0m");
	else if (state == STATE_THINK)
		return (" is \x1b[35mthinking\x1b[0m");
	else if (state == STATE_DIED)
		return (" \x1b[31mdied\x1b[0m");
	else if (state == STATE_END)
		return ("\x1b[31mreaching the number philo must eat\x1b[0m");
	return (NULL);
}

void		put_message(t_philo *philo, int state)
{
	uint64_t	cur_time;
	static int	done = 1;

	pthread_mutex_lock(&philo->state->message_m);
	cur_time = get_cur_time();
	if (done)
	{
		if (state == STATE_END)
		{
			printf("%llums\t%s\n", (cur_time - philo->state->start_time), \
				choose_message(state));
			done = 0;
		}
		else if (state == STATE_DIED)
		{
			printf("%llums\t%d%s\n", (cur_time - philo->state->start_time), \
				philo->philo_index + 1, choose_message(state));
			done = 0;
		}
		else
			printf("%llums\t%d%s\n", (cur_time - philo->state->start_time), \
				philo->philo_index + 1, choose_message(state));
	}
	pthread_mutex_unlock(&philo->state->message_m);
}
