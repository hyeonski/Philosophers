/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:22:42 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 19:58:37 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void		ft_eat(t_philo *philo)
{
	sem_wait(philo->env->forks_sem);
	sem_wait(philo->env->forks_sem);
	sem_wait(philo->env->print_sem);
	ft_put_msg(philo, EVENT_FORK);
	sem_post(philo->env->print_sem);
	philo->t_last_eat = ft_get_time();
	philo->n_eaten++;
	sem_wait(philo->env->print_sem);
	ft_put_msg(philo, EVENT_EAT);
	sem_post(philo->env->print_sem);
	ft_my_sleep(philo->env->t_to_eat);
	sem_post(philo->env->forks_sem);
	sem_post(philo->env->forks_sem);
}

void		ft_sleep_and_think(t_philo *philo)
{
	sem_wait(philo->env->print_sem);
	ft_put_msg(philo, EVENT_SLEEP);
	sem_post(philo->env->print_sem);
	ft_my_sleep(philo->env->t_to_sleep);
	sem_wait(philo->env->print_sem);
	ft_put_msg(philo, EVENT_THINK);
	sem_post(philo->env->print_sem);
}

void		ft_die(t_philo *philo)
{
	sem_wait(philo->env->print_sem);
	ft_put_msg(philo, EVENT_DIED);
	sem_post(philo->env->print_sem);
}
