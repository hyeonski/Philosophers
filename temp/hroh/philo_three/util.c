/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:09:14 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 22:26:32 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_my_sleep(long t_sleep)
{
	struct timeval	tv;
	long			end;
	long			now;

	gettimeofday(&tv, NULL);
	end = tv.tv_sec * 1000000 + tv.tv_usec + t_sleep * 1000;
	while (1)
	{
		gettimeofday(&tv, NULL);
		now = tv.tv_sec * 1000000 + tv.tv_usec;
		if (now < end)
			usleep(800);
		else
			return ;
	}
}

long	ft_get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int		ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
	|| c == '\v' || c == '\f' || c == '\r');
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}
