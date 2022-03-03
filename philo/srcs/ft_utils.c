/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:34:33 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 05:42:29 by adben-mc         ###   ########.fr       */
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

int	get_time(struct timeval *debut)
{
	struct timeval	fin;

	gettimeofday(&fin, NULL);
	return ((1e3 * ((&fin)->tv_sec - debut->tv_sec))
		+ (1e-3 * ((&fin)->tv_usec - debut->tv_usec)));
}

void	ft_sleep(int time, t_data *data)
{
	struct timeval	debut;

	gettimeofday(&debut, NULL);
	while (get_time(&debut) < time && !ft_checkdead(data))
		usleep(200);
}

int	ft_checkdead(t_data *data)
{
	pthread_mutex_lock(&data->status_m);
	if (data->status)
	{
		pthread_mutex_unlock(&data->status_m);
		return (1);		
	}
	pthread_mutex_unlock(&data->status_m);
	return (0);
}

// 1 taken fork, 2 is eating, 3 is sleeping, 4 is thinking, 5 is dead
// x value
void	ft_output(int x, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->status_m));
	if (!philo->data->status) // not dead
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%d %d ", get_time(&(philo->data->time)), philo->id);
		if (x == 1)
			printf("has taken a fork\n");
		else if (x == 2)
			printf("is eating\n");
		else if (x == 3)
			printf("is sleeping\n");
		else if (x == 4)
			printf("is thinking\n");
		else if (x == 5)
			printf("died\n");
		pthread_mutex_unlock(&(philo->data->print));
	}
	pthread_mutex_unlock(&(philo->data->status_m));
}