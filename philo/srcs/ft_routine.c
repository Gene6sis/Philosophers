/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/28 06:20:07 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//((t_philo *)p)

int	ft_deadcheck(t_philo *philo)
{
	if (get_time(&(philo->data->time)) - philo->last_eat > philo->data->dead_time)
	{
		printf("%d\t%d died\n", get_time(&(philo->data->time)), philo->id);
		exit(EXIT_SUCCESS);
		return (1);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	// printf("eat %d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
	pthread_mutex_lock(&(philo->fork));
	if (!ft_deadcheck(philo))
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%d\t%d has taken a fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	// printf("eat %d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
	pthread_mutex_lock(&(philo->right->fork));
	if (!ft_deadcheck(philo))
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%d\t%d has taken a fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	philo->last_eat = get_time(&(philo->data->time));
	if (!ft_deadcheck(philo))
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%d\t%d is eating\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	ft_sleep(philo->data->eat_time);
	pthread_mutex_unlock(&(philo->fork));
	// printf("eat %d\t%d drop the fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
	pthread_mutex_unlock(&(philo->right->fork));
	// printf("eat %d\t%d drop the fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
}

void	ft_sleeping(t_philo *philo)
{
	if (!ft_deadcheck(philo))
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%d\t%d is sleeping\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	ft_sleep(philo->data->sleep_time);
}

void	ft_thinking(t_philo *philo)
{
	if (!ft_deadcheck(philo))
	{
		pthread_mutex_lock(&(philo->data->print));
		printf("%d\t%d is thinking\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
}


void	*routine(void *p)
{
	((t_philo *)p)->last_eat = 0;
	while (1)
	{
		ft_eat((t_philo *)p);
		ft_sleeping((t_philo *)p);
		ft_thinking((t_philo *)p);
	}
	return (0);
}