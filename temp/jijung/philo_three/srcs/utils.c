/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijung <jijung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:56:32 by jijung            #+#    #+#             */
/*   Updated: 2021/03/03 04:29:35 by jijung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

int			ft_str_isdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(48 <= str[i] && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		ma;
	int		res;

	i = 0;
	ma = 1;
	res = 0;
	while (str[i] && ((9 <= str[i] && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ma = -1;
		i++;
	}
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		if (res < 0 && ma < 0)
			return (0);
		if (res < 0 && ma > 0)
			return (-1);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * ma);
}

uint64_t	get_cur_time(void)
{
	struct timeval		time;
	unsigned int		current_time;

	gettimeofday(&time, NULL);
	current_time = ((uint64_t)time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

void		new_sleep(uint64_t wait_time)
{
	uint64_t	target_time;

	target_time = wait_time + get_cur_time();
	while (target_time > get_cur_time())
		;
}
