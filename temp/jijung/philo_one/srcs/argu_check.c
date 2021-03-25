/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argu_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:47:45 by jijung            #+#    #+#             */
/*   Updated: 2021/03/04 06:19:06 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int		argu_check(int argc, char **argv)
{
	if (!argu_input_check(argc, argv))
	{
		printf("1 - number_of_philosophers\n");
		printf("2 - time_to_die\n");
		printf("3 - time_to_eat\n");
		printf("4 - time_to_sleep\n");
		printf("5 - number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	return (1);
}

int		argu_input_check(int argc, char **argv)
{
	int i;

	if (argc < 5 || argc > 6)
	{
		printf("error : check the agument.\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_str_isdigit(argv[i]) || ft_atoi(argv[i]) < 0)
		{
			printf("enter only positive integer.\n");
			return (0);
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 2)
	{
		printf("requires at least two philosophers.\n");
		return (0);
	}
	return (1);
}
