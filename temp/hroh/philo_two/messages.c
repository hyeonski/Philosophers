/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:59:40 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 19:58:43 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_put_msg(t_philo *philo, int event_t)
{
	char *buf;

	buf = ft_itoa(ft_get_time() - philo->env->start);
	buf = ft_strjoin(buf, "\t", 1);
	buf = ft_strjoin(buf, ft_itoa(philo->index + 1), 3);
	if (event_t == EVENT_FORK)
		buf = ft_strjoin(buf, " has taken a fork\n", 1);
	else if (event_t == EVENT_EAT)
		buf = ft_strjoin(buf, " is eating\n", 1);
	else if (event_t == EVENT_SLEEP)
		buf = ft_strjoin(buf, " is sleeping\n", 1);
	else if (event_t == EVENT_THINK)
		buf = ft_strjoin(buf, " is thinking\n", 1);
	else if (event_t == EVENT_DIED)
		buf = ft_strjoin(buf, " died\n", 1);
	write(1, buf, ft_strlen(buf));
	if (event_t == EVENT_FORK)
		write(1, buf, ft_strlen(buf));
	free(buf);
}
