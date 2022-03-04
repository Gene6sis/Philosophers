/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:52:00 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/04 18:01:15 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_stop(t_data *data)
{
	pthread_mutex_lock(&data->status_m);
	data->status = 1;
	pthread_mutex_unlock(&data->status_m);
}

int	time_diff(int tv1, int tv2)
{
	return (tv2 - tv1);
}

int	ft_deathcheck(t_philo *philo, t_data *data, int time)
{
	pthread_mutex_lock(&philo->last_eat);
	if (time_diff(philo->last_eat_time, time) >= data->dead_time)
	{
		ft_output(5, philo);
		ft_stop(data);
		pthread_mutex_unlock(&philo->last_eat);
		return (0);
	}
	pthread_mutex_unlock(&philo->last_eat);
	return (1);
}

void	ft_manager(t_data *data)
{
	t_philo			*philo;
	int				status;
	int				i;

	status = 1;
	philo = data->philo;
	while (status)
	{
		i = -1;
		while (status && ++i < data->nb_philo)
		{
			status = ft_deathcheck(philo, data, get_time(&data->time));
			if (!status)
				return ;
			pthread_mutex_lock(&data->eat_m);
			if (data->total_eat == data->nb_philo)
			{
				ft_stop(data);
				status = 0;
			}
			pthread_mutex_unlock(&data->eat_m);
		}
		if (status)
			usleep(500);
	}
}
