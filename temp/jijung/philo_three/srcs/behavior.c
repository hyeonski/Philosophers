/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:55:44 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 01:55:45 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

void		hold_forks(t_philo *philo)
{
	sem_wait(philo->state->fork_s);
	put_message(philo, STATE_FORK);
	sem_wait(philo->state->fork_s);
	put_message(philo, STATE_FORK);
}

void		eating(t_philo *philo)
{
	sem_wait(philo->check_s);
	philo->now_eating = 1;
	philo->last_eat = get_cur_time();
	philo->limit_time = philo->last_eat + philo->state->time_to_die;
	put_message(philo, STATE_EAT);
	new_sleep(philo->state->time_to_eat);
	philo->eating_count++;
	philo->now_eating = 0;
	sem_post(philo->check_s);
}

void		drop_forks(t_philo *philo)
{
	sem_post(philo->state->fork_s);
	sem_post(philo->state->fork_s);
}

void		sleep_think(t_philo *philo)
{
	put_message(philo, STATE_SLEEP);
	new_sleep(philo->state->time_to_sleep);
	put_message(philo, STATE_THINK);
}
