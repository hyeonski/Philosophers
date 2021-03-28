/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:39:45 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 23:17:10 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int		ft_clear(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->n_philo)
	{
		kill(env->p[i]->pid, SIGKILL);
		free(env->p[i]);
	}
	free(env->p);
	free(env);
	return (0);
}