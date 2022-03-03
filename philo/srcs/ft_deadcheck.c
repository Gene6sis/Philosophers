/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deadcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:20:12 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 01:11:12 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_dead(t_philo *philo, int status)
{
	if ((status == 1 && philo->id % 2 == 0)

		|| (status == 2 && philo->id % 2 == 1)

		|| status == 3 || status == 4)

		pthread_mutex_unlock(&(philo->fork));
	if ((status == 1 && philo->id % 2 == 1)

		|| (status == 2 && philo->id % 2 == 0)
			
		|| status == 3 || status == 4)
		pthread_mutex_unlock(&(philo->right->fork));
	if (status != 4 && status != 6 && status != 0
			&& status != 12)
		pthread_mutex_unlock(&(philo->data->print));
	pthread_mutex_unlock(&(philo->data->m_status));
	return (1);
}

int	ft_deadcheck(t_philo *philo, int status)
{
	pthread_mutex_lock(&(philo->data->m_status));
	if (philo->data->status == 1)
		return(ft_dead(philo, status));
	pthread_mutex_unlock(&(philo->data->m_status));
	if (philo->data->status != 1 && get_time(&(philo->data->time)) - philo->last_eat > philo->data->dead_time)
	{
		pthread_mutex_lock(&(philo->data->m_status));
		philo->data->status = 1;
		printf("%d %d died\n", get_time(&(philo->data->time)), philo->id);
		return (ft_dead(philo, status));
	}
	pthread_mutex_unlock(&(philo->data->m_status));
	return (0);
}