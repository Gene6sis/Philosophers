/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 01:03:26 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	ft_fork(philo);
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo, 3))
	{
		printf("%d %d is eating\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
		philo->nb_eat++;
	}
	if (!ft_deadcheck(philo, 4))
		ft_sleep(philo->data->eat_time, philo, 4);
	if (!ft_deadcheck(philo, 4))
	{
		pthread_mutex_unlock(&(philo->fork));
		// printf("%d\t%d drop the fork middl[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
		pthread_mutex_unlock(&(philo->right->fork));
		// printf("%d\t%d drop the fork right[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
	}
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo, 5))
	{
		printf("%d %d is sleeping\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	ft_sleep(philo->data->sleep_time, philo, 6);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo, 7))
	{
		printf("%d %d is thinking\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->last_eat = 0;
	philo->islock = 0;
	if (philo->id % 2 == 0 && philo->data->nb_philo != 1)
		ft_sleep(philo->data->eat_time / 2, philo, 0);
	if (philo->data->nb_philo == 1)
	{
		ft_sleep(philo->data->dead_time, philo, 0);
		printf("%d %d died\n", get_time(&(philo->data->time)), philo->id);
		return (0);
	}
	philo->nb_eat = 0;
	while (!philo->data->status && (philo->nb_eat < philo->data->have_to_eat
			|| philo->data->have_to_eat == -1))
	{
		ft_eat(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (0);
}