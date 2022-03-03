/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:57:01 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 02:29:28 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atolcheck(char *str, long max, long min)
{
	long	i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		result = result * 10 + (long)str[i++] - '0';
	if ((result * sign) > max || (result * sign) < min || ft_strlen(str) > 11)
		return (0);
	return (1);
}

int	ft_have_nb(char *str)
{
	size_t	i;
	size_t	compt;

	if (ft_strlen(str) == 0)
		return (0);
	i = 0;
	compt = 0;
	while (str[i])
	{
		if (ft_strchr("0123456789", str[i]))
			compt++;
		i++;
	}
	return (compt);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_checkarg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_strchr("0123456789", argv[i][j]))
				return (0);
			j++;
		}
		if (!ft_have_nb(argv[i]) || !ft_strlen(argv[i])
			|| !ft_atolcheck(argv[i], 2147483647, -2147483648)
			|| ft_atoi(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		result = result * 10 + (int)str[i++] - '0';
	return (result * sign);
}
