/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:54:28 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 04:22:00 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

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

	sem_wait(philo->state->message_s);
	sem_wait(philo->state->die_message_s);
	cur_time = get_cur_time();
	if (state == STATE_END)
		printf("%llums\t%s\n", (cur_time - philo->state->start_time), \
				choose_message(state));
	else if (state == STATE_DIED)
		printf("%llums\t%d%s\n", (cur_time - philo->state->start_time), \
				philo->philo_index + 1, choose_message(state));
	else
		printf("%llums\t%d%s\n", (cur_time - philo->state->start_time), \
				philo->philo_index + 1, choose_message(state));
	if (state < STATE_DIED)
		sem_post(philo->state->die_message_s);
	sem_post(philo->state->message_s);
}
