/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deadcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:20:12 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/02 18:46:20 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_dead(t_philo *philo, int status)
{
	if (status == 1 || status == 2 || status == 3 || status == 4)
		pthread_mutex_unlock(&(philo->fork));
	if (status == 2 || status == 3 || status == 4)
		pthread_mutex_unlock(&(philo->right->fork));
	if (status != 4 && status != 6 && status != 0
			&& status != 12)
		pthread_mutex_unlock(&(philo->data->print));
	return (1);
}

int	ft_deadcheck(t_philo *philo, int status)
{
	if (philo->data->status == 1)
		return(ft_dead(philo, status));
	else if (get_time(&(philo->data->time)) - philo->last_eat > philo->data->dead_time)
	{
		philo->data->status = 1;
		printf("%d %d died\n", get_time(&(philo->data->time)), philo->id);
		return (ft_dead(philo, status));
	}
	return (0);
}