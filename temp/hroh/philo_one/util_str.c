/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 00:13:54 by hroh              #+#    #+#             */
/*   Updated: 2021/03/19 00:15:22 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int		ft_strlen(const char *str)
{
	int s;

	s = 0;
	while (str[s] != 0)
		s++;
	return (s);
}

int		ft_strlcpy(char *dest, const char *src, int size)
{
	int s;
	int src_len;

	s = 0;
	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[s] && s < size - 1)
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = 0;
	return (src_len);
}

char	*ft_strdup(const char *str)
{
	char	*re;
	int		len;

	len = ft_strlen(str);
	if (!(re = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(re, str, len + 1);
	return (re);
}

char	*ft_strjoin(char *s1, char *s2, int free_case)
{
	char	*re;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(re = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	ft_strlcpy(re, s1, s1_len + 1);
	if (free_case == 1 || free_case == 3)
		free(s1);
	ft_strlcpy(re + s1_len, s2, s2_len + 1);
	if (free_case == 2 || free_case == 3)
		free(s2);
	return (re);
}

int		ft_putstr(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (0);
}
