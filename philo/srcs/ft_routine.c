/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/02 02:55:30 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//((t_philo *)p)

// void	ft_finish(t_philo *philo)
// {
	
// }

int	ft_deadcheck(t_philo *philo)
{
	if (philo->data->status == 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->right->fork));
		pthread_mutex_unlock(&(philo->data->print));
		return (1);
	}
	else if (get_time(&(philo->data->time)) - philo->last_eat > philo->data->dead_time)
	{
		philo->data->status = 1;
		printf("%d %d died\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->right->fork));
		pthread_mutex_unlock(&(philo->data->print));
		return (1);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	// printf("%d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
	pthread_mutex_lock(&(philo->fork));
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d %d has taken a fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	// printf("%d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
	pthread_mutex_lock(&(philo->right->fork));
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		philo->last_eat = get_time(&(philo->data->time));
		printf("%d %d has taken a fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d %d is eating\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	if (!ft_deadcheck(philo))
		ft_sleep(philo->data->eat_time, philo);
	pthread_mutex_unlock(&(philo->fork));
	// printf("%d\t%d drop the fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
	pthread_mutex_unlock(&(philo->right->fork));
	// printf("%d\t%d drop the fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d %d is sleeping\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	ft_sleep(philo->data->sleep_time, philo);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d %d is thinking\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
}

void	*routine(void *p)
{
	((t_philo *)p)->last_eat = 0;
	if (((t_philo *)p)->id % 2 == 0 && ((t_philo *)p)->data->nb_philo != 1)
		ft_sleep(((t_philo *)p)->data->eat_time / 2, ((t_philo *)p));
	if (((t_philo *)p)->data->nb_philo == 1)
	{
		ft_sleep(((t_philo *)p)->data->dead_time, ((t_philo *)p));
		printf("%d %d died\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id);
		return (0);
	}
	while (!((t_philo *)p)->data->status)
	{
		// if (((t_philo *)p)->last_eat - get_time(&(((t_philo *)p)->data->time)) > ((t_philo *)p)->data->dead_time * 1.5)
			// ft_sleep(((t_philo *)p)->data->dead_time / 3, ((t_philo *)p));
		ft_eat((t_philo *)p);
		ft_sleeping((t_philo *)p);
		ft_thinking((t_philo *)p);
	}
	return (0);
}