/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:46:13 by hyeonski          #+#    #+#             */
/*   Updated: 2021/03/25 17:19:39 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int parse_arg(t_table *table, char **argv)
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
	int	i;

	i = 0;
	while (argv[i])
	{
		if (i == 1 && (!is_str_digit(argv[i]) || (table->num_of_philos = ft_atoi(argv[i]) <= 0)))
			return (1);
		if (i == 2 && (!is_str_digit(argv[i]) || (table->time_to_die = ft_atoi(argv[i]) <= 0)))
			return (1);
		if (i == 3 && (!is_str_digit(argv[i]) || (table->time_to_eat = ft_atoi(argv[i]) <= 0)))
			return (1);
		if (i == 4 && (!is_str_digit(argv[i]) || (table->time_to_sleep = ft_atoi(argv[i]) <= 0)))
			return (1);
		if (i == 5 && (!is_str_digit(argv[i]) || (table->num_of_must_eat = ft_atoi(argv[i]) <= 0)))
			return (1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table, t_philo *philos)
{
	
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (p_error("Error: bad arguments\n"));
	if (parse_arg(&table, argv))
		return (p_error("Error: bad arguments\n"));
	if (!(philos = malloc(sizeof(t_philo) * table.num_of_philos)))
		return (p_error("Error: malloc failed\n"));
	init_table(&table, philos);
	clean_table(&table, philos);
	return (0);
}
