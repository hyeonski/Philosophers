/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:12:15 by hyeonski          #+#    #+#             */
/*   Updated: 2021/04/01 10:07:29 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					ft_atoi(const char *str)
{
	int				i;
	int				sign;
	int				result;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int					p_error(char *err_msg)
{
	printf("%s", err_msg);
	return (1);
}

int					is_str_digit(char *str)
{
	int				i;

	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

unsigned long		get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int					parse_num_arg(char *str)
{
	int				i;
	int				ret;

	i = 0;
	if (!is_str_digit(str))
		return (-1);
	ret = ft_atoi(str);
	if (ret <= 0)
		return (-1);
	else
		return (ret);
}
