/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 00:15:02 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 00:15:13 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int		ft_num_len(long n)
{
	int len;

	len = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(long n)
{
	char			*re;
	long			us_n;
	int				len;

	len = ft_num_len(n);
	if (!(re = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	us_n = n;
	re[len] = 0;
	len--;
	while (len >= 0)
	{
		re[len] = '0' + (us_n % 10);
		us_n = us_n / 10;
		len--;
	}
	return (re);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	re;

	i = 0;
	sign = 1;
	re = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] == '-')
		sign = -1;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		re = re * 10 + str[i] - '0';
		i++;
	}
	return (re * sign);
}

void	ft_putnbr_fd(long n, int fd)
{
	long	nbr;
	char	c;

	nbr = n;
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	c = nbr % 10 + '0';
	write(fd, &c, 1);
}
