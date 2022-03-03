/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:41:16 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 01:04:42 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_fork_order(t_philo *philo, int step)
{
	if ((step == 1 && philo->id % 2 == 0) || (step == 2 && philo->id % 2 == 1))
	{
		pthread_mutex_lock(&(philo->fork));
		philo->islock = 1;
	}
	if ((step == 2 && philo->id % 2 == 0) || (step == 1 && philo->id % 2 == 1))
	{
		pthread_mutex_lock(&(philo->right->fork));
		philo->right->islock = 1;
	}
}

void	ft_fork(t_philo *philo)
{
	// printf("%d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
	ft_fork_order(philo, 1);
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo, 1))
	{
		printf("%d %d has taken a fork\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	// printf("%d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
	ft_fork_order(philo, 2);
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo, 2))
	{
		philo->last_eat = get_time(&(philo->data->time));
		printf("%d %d has taken a fork\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
}