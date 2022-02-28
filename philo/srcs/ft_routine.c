/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:34 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/28 05:35:25 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//((t_philo *)p)
void	*routine(void *p)
{
	((t_philo *)p)->last_eat = -1;
	while (1)
	{
		// printf("eat %d\t%d tr to take fork[%d]\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id, ((t_philo *)p)->id);
		pthread_mutex_lock(&(((t_philo *)p)->fork));
		printf("%d\t%d has taken a fork[%d]\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id, ((t_philo *)p)->id);
		// printf("eat %d\t%d tr to take fork[%d]\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id, ((t_philo *)p)->right->id);
		pthread_mutex_lock(&(((t_philo *)p)->right->fork));
		printf("%d\t%d has taken a fork[%d]\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id, ((t_philo *)p)->right->id);
		printf("%d\t%d is eating\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id);
		ft_sleep(((t_philo *)p)->data->eat_time);
		pthread_mutex_unlock(&(((t_philo *)p)->fork));
		// printf("eat %d\t%d drop the fork[%d]\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id, ((t_philo *)p)->id);
		pthread_mutex_unlock(&(((t_philo *)p)->right->fork));
		// printf("eat %d\t%d drop the fork[%d]\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id, ((t_philo *)p)->right->id);
		printf("%d\t%d is sleeping\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id);
		ft_sleep(((t_philo *)p)->data->sleep_time);
		printf("%d\t%d is thinking\n", get_time(&(((t_philo *)p)->data->time)), ((t_philo *)p)->id);
	}
	return (0);
}