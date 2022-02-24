/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:57:01 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/19 19:37:04 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atolcheck(char *str, long max, long min)
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
			if (!ft_strchr("-0123456789", argv[i][j]))
				return (0);
			j++;
		}
		if (!ft_have_nb(argv[i]) || !ft_strlen(argv[i])
			|| !ft_atolcheck(argv[i], 2147483647, -2147483648))
			return (0);
		i++;
	}
	return (1);
}
