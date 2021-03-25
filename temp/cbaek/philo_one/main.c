/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:27:33 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/23 18:34:47 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	parse(t_table *table, char **argv)
{
	table->num_eat = -1;
	if ((table->num_of_philos = (unsigned long)(ft_atoi(argv[1]))) <= 0 ||
		(table->time_to_die = (unsigned long)(ft_atoi(argv[2]))) <= 0 ||
		(table->time_to_eat = (unsigned long)(ft_atoi(argv[3]))) <= 0 ||
		(table->time_to_sleep = (unsigned long)(ft_atoi(argv[4]))) <= 0)
		return (FAILURE);
	if (argv[5] && (table->num_eat = (unsigned long)(ft_atoi(argv[5]))) <= 0)
		return (FAILURE);
	return (SUCCESS);
}

static void	destroy_all(t_table *table)
{
	int	idx;

	pthread_mutex_destroy(&table->m_msg);
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->m_dead);
	idx = 0;
	while (idx < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->m_forks[idx]);
		idx++;
	}
}

static void	set_philos(t_philo *philos, t_table *table)
{
	int idx;

	idx = 0;
	while (idx < table->num_of_philos)
	{
		philos[idx].nbr = idx + 1;
		if (idx == 0)
			philos[idx].fork1 = table->num_of_philos - 1;
		else
			philos[idx].fork1 = idx - 1;
		philos[idx].fork2 = idx;
		philos[idx].cnt_eat = 0;
		philos[idx].table = table;
		philos[idx].last_meal = get_time();
		pthread_create(&philos[idx].tid, NULL, exec_act, &philos[idx]);
		idx++;
	}
}

static int	set_table(t_table *table)
{
	int	idx;

	pthread_mutex_init(&table->m_msg, NULL);
	pthread_mutex_init(&table->m_eat, NULL);
	pthread_mutex_init(&table->m_dead, NULL);
	if (!(table->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			table->num_of_philos)))
		return (FAILURE);
	idx = 0;
	while (idx < table->num_of_philos)
	{
		pthread_mutex_init(&table->m_forks[idx], NULL);
		idx++;
	}
	table->base_time = get_time();
	table->is_dead = FALSE;
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;
	int		idx;

	if (!(4 < argc && argc < 7))
		return (put_error("put 5 or 6 arguments"));
	if (parse(&table, argv))
		return (put_error("invalid arguments"));
	if (set_table(&table))
		return (put_error("malloc failed"));
	if (!(philos = (t_philo *)malloc((sizeof(t_philo) * table.num_of_philos))))
		return (FAILURE);
	set_philos(philos, &table);
	idx = 0;
	while (idx < table.num_of_philos)
	{
		pthread_join(philos[idx].tid, NULL);
		idx++;
	}
	destroy_all(&table);
	free(philos);
	free(table.m_forks);
	return (SUCCESS);
}
