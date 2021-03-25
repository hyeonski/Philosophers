/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:53:57 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 23:55:31 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*ft_full_wait(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->env->full_sem);
	return (0);
}

void	*ft_full_end(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	sem_wait(env->full_sem);
	sem_post(env->end_sem);
	return (0);
}
