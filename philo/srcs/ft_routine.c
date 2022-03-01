/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/01 14:04:03 by adben-mc         ###   ########.fr       */
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
		printf("%d\t%d died\n", get_time(&(philo->data->time)), philo->id);
		philo->data->status = 1;
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->right->fork));
		pthread_mutex_unlock(&(philo->data->print));
		return (1);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	// printf("eat %d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);

	// if (philo->left->last_eat >= philo->last_eat)
	pthread_mutex_lock(&(philo->fork));
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d\t%d has taken a fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	// printf("eat %d\t%d tr to take fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
	// if (philo->right->last_eat >= philo->last_eat)
	pthread_mutex_lock(&(philo->right->fork));
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d\t%d has taken a fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	philo->last_eat = get_time(&(philo->data->time));
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d\t%d is eating\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	if (!ft_deadcheck(philo))
		ft_sleep(philo->data->eat_time);
	pthread_mutex_unlock(&(philo->fork));
	// printf("eat %d\t%d drop the fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->id);
	pthread_mutex_unlock(&(philo->right->fork));
	// printf("eat %d\t%d drop the fork[%d]\n", get_time(&(philo->data->time)), philo->id, philo->right->id);
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d\t%d is sleeping\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
	ft_sleep(philo->data->sleep_time);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	if (!ft_deadcheck(philo))
	{
		printf("%d\t%d is thinking\n", get_time(&(philo->data->time)), philo->id);
		pthread_mutex_unlock(&(philo->data->print));
	}
}

void	*routine(void *p)
{
	((t_philo *)p)->last_eat = 0;
	if (((t_philo *)p)->id % 2 == 0 && ((t_philo *)p)->data->nb_philo != 1)
		ft_sleep(((t_philo *)p)->data->eat_time);
	if (((t_philo *)p)->data->nb_philo == 1)
	{
		ft_sleep(((t_philo *)p)->data->dead_time);
		printf("%d\t%d died\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id);
		return (0);
	}
	while (((t_philo *)p)->data->status == 0)
	{
		// printf("a1\n");
		ft_eat((t_philo *)p);
		// printf("a2\n");
		// printf("b1\n");
		ft_sleeping((t_philo *)p);
		// printf("b2\n");
		// printf("c1\n");
		ft_thinking((t_philo *)p);
		// printf("c2\n");
	}
	return (0);
}