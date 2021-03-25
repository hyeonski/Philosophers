/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:47:55 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 05:07:47 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

void		hold_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->fork_m[philo->fork_r]);
	put_message(philo, STATE_FORK);
	pthread_mutex_lock(&philo->state->fork_m[philo->fork_l]);
	put_message(philo, STATE_FORK);
}

void		eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_m);
	philo->now_eating = 1;
	philo->last_eat_time = get_cur_time();
	philo->limit_time = philo->last_eat_time + philo->state->time_to_die;
	put_message(philo, STATE_EAT);
	new_sleep(philo->state->time_to_eat);
	philo->eating_count++;
	philo->now_eating = 0;
	pthread_mutex_unlock(&philo->check_m);
}

void		drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->fork_m[philo->fork_r]);
	pthread_mutex_unlock(&philo->state->fork_m[philo->fork_l]);
}

void		sleep_think(t_philo *philo)
{
	put_message(philo, STATE_SLEEP);
	new_sleep(philo->state->time_to_sleep);
	put_message(philo, STATE_THINK);
}
