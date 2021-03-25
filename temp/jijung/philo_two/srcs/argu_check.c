/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argu_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:53:43 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 03:41:53 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

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
		if (!ft_str_isdigit(argv[i]))
		{
			printf("enter only positive numbers.\n");
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
