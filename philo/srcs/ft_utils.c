/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:34:33 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/27 00:37:59 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
	}
	if ((char)c == s[i])
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
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

void	printphilo(t_data *data)
{
	int i;
	t_philo *cur;
	cur = data->philo;
	i = 0;
	while (i < data->nb_philo * 3)
	{
		printf("[%d] id : %d\n", i, cur->id);
		i++;
		if (data->nb_philo > 1)
			cur = cur->right;
	}
	i--;
	while (i >= 0)
	{
		printf("[%d] id : %d\n", i, cur->id);
		i--;
		if (data->nb_philo > 1)
			cur = cur->left;
	}
}