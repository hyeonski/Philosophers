/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:03:10 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/25 12:03:57 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

static void	unlink_sems(void)
{
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/dead");
	sem_unlink("/msg");
}

static void	set_philos(t_philo *philos, t_table *table)
{
	int idx;

	idx = 0;
	while (idx < table->num_of_philos)
	{
		philos[idx].nbr = idx + 1;
		philos[idx].cnt_eat = 0;
		philos[idx].table = table;
		philos[idx].last_meal = get_time();
		idx++;
	}
	idx = 0;
	while (idx < table->num_of_philos)
	{
		philos[idx].pid = fork();
		if (philos[idx].pid == 0)
			break ;
		idx++;
	}
	if (idx != philos->table->num_of_philos)
		exec_act(&philos[idx]);
	else
		process_monitor(philos);
	exit(EXIT_SUCCESS);
}

static int	set_table(t_table *table)
{
	table->sm_forks = sem_open("/fork", O_CREAT | O_EXCL, 0644, \
			table->num_of_philos);
	table->sm_eat = sem_open("/eat", O_CREAT | O_EXCL, 0644, 1);
	table->sm_dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	table->sm_msg = sem_open("/msg", O_CREAT | O_EXCL, 0644, 1);
	table->base_time = get_time();
	table->is_dead = FALSE;
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	unlink_sems();
	if (!(4 < argc && argc < 7))
		return (put_error("put 5 or 6 arguments"));
	if (parse(&table, argv))
		return (put_error("invalid arguments"));
	if (set_table(&table))
		return (put_error("malloc failed"));
	if (!(philos = (t_philo *)malloc((sizeof(t_philo) * table.num_of_philos))))
		return (FAILURE);
	set_philos(philos, &table);
	free(philos);
	return (SUCCESS);
}
