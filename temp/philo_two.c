/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 22:08:20 by hyeonski          #+#    #+#             */
/*   Updated: 2021/02/11 22:11:52 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t *m_right_fork;

void	eating()
{
	if (is_alive())
	{
		pthread_mutex_lock(m_right_fork);
	}
}