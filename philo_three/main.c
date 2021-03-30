/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 19:03:33 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/30 20:14:29 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	p_error(char *err_msg)
{
	printf("%s", err_msg);
	return (1);
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static int	parse_num_arg(char *str)
{
	int		i;
	int		ret;

	i = 0;
	if (!is_str_digit(str))
		return (-1);
	ret = ft_atoi(str);
	if (ret <= 0)
		return (-1);
	else
		return (ret);
}

static int	parse_arg(t_table *table, char **argv)
{
	int		i;

	table->num_to_eat = -1;
	i = 1;
	while (argv[i])
	{
		if (i == 1 && (table->num_of_philos = parse_num_arg(argv[i])) == -1)
			return (1);
		if (i == 2 && (table->time_to_die = parse_num_arg(argv[i])) == -1)
			return (1);
		if (i == 3 && (table->time_to_eat = parse_num_arg(argv[i])) == -1)
			return (1);
		if (i == 4 && (table->time_to_sleep = parse_num_arg(argv[i])) == -1)
			return (1);
		if (i == 5 && (table->num_to_eat = parse_num_arg(argv[i])) == -1)
			return (1);
		i++;
	}
	return (0);
}

static void	unlink_sems(void)
{
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/dead");
	sem_unlink("/msg");
}

static int	init_table(t_table *table)
{
	table->s_forks = sem_open("/fork",  O_CREAT | O_EXCL, 0644, table->num_of_philos);
	table->s_eat = sem_open("/eat", O_CREAT | O_EXCL, 0644, 1);
	table->s_dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	table->s_msg = sem_open("/msg", O_CREAT | O_EXCL, 0644, 1);
	table->base_time = get_time();
	table->is_dead = FALSE;
	return (0);
}

static void	init_philos(t_philo *philos, t_table *table)
{
	int		i;

	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i].num = i + 1;
		philos[i].cnt_eat = 0;
		philos[i].table = table;
		philos[i].last_eat = get_time();
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			break ;
		i++;
	}
	// i = 0;
	// while (i < table->num_of_philos)
	// {
	// 	philos[i].pid = fork();
	// 	if (philos[i].pid == 0)
	// 		break ;
	// 	i++;
	// }
	if (i != philos->table->num_of_philos)
		eat_routine(&philos[i]);
	else
		philo_monitor(philos);
}

void		clean_table(t_table *table, t_philo *philos)
{
	unlink_sems();
	sem_close(table->s_forks);
	sem_close(table->s_eat);
	sem_close(table->s_dead);
	sem_close(table->s_msg);
	free(philos);
}

int			main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;
	int		i;

	unlink_sems();
	if (!(5 <= argc && argc <= 6))
		return (p_error("Error: put right number of arguments\n"));
	if (parse_arg(&table, argv))
		return (p_error("Error: bad arguments\n"));
	if (init_table(&table))
		return (p_error("Error: malloc failed\n"));
	if (!(philos = (t_philo *)malloc((sizeof(t_philo) * table.num_of_philos))))
		return (1);
	init_philos(philos, &table);
	clean_table(&table, philos);
	return (0);
}