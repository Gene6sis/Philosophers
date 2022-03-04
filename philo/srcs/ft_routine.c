/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/04 04:09:36 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&philo->fork);
	else
		pthread_mutex_lock(&philo->right->fork);
	ft_output(1, philo);
	if (philo->id % 2)
		pthread_mutex_lock(&philo->right->fork);
	else
		pthread_mutex_lock(&philo->fork);
	ft_output(1, philo);
	ft_output(2, philo);
	pthread_mutex_lock(&(philo->last_eat));
	philo->last_eat_time = get_time(&philo->data->time);
	pthread_mutex_unlock(&(philo->last_eat));
	ft_sleep(philo->data->eat_time, philo->data);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
	if (++philo->nb_eat == philo->data->have_to_eat)
	{
		pthread_mutex_lock(&philo->data->eat_m);
		philo->data->total_eat++;
		pthread_mutex_unlock(&philo->data->eat_m);
	}
}

void	*routine(void *p)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)p;
	data = philo->data;
	if (!(philo->id % 2))
		ft_sleep(philo->data->eat_time / 2, data);
	if (philo->data->nb_philo == 1)
		ft_output(1, philo);
	while (data->nb_philo > 1 && !ft_checkdead(data))
	{
		ft_eat(philo);
		ft_output(3, philo);
		ft_sleep(data->sleep_time, data);
		ft_output(4, philo);
		if (data->nb_philo % 2)
			ft_sleep(data->eat_time, data);
	}
	return (0);
}