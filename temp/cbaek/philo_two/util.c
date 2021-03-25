/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:01:16 by cbaek             #+#    #+#             */
/*   Updated: 2021/03/24 16:58:12 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				ft_atoi(const char *str)
{
	int	idx;
	int	result;
	int	sign;

	idx = 0;
	result = 0;
	sign = 0;
	while (str[idx] == ' ' || (str[idx] > 8 && str[idx] < 14))
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		sign = -(str[idx++] - 44);
	if (str[idx] >= '0' && str[idx] <= '9')
	{
		if (sign == 0)
			sign = 1;
		while (str[idx] >= '0' && str[idx] <= '9')
			result = (result * 10) + (str[idx++] - '0');
	}
	return (sign * result);
}

int				put_error(const char *str)
{
	printf("Error: %s\n", (char *)str);
	return (FAILURE);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void			vsleep(unsigned long itime)
{
	unsigned long	stime;
	unsigned long	ctime;

	stime = get_time();
	while (TRUE)
	{
		ctime = get_time();
		if (ctime - stime > itime)
			return ;
		usleep(U_DELAY);
	}
}
