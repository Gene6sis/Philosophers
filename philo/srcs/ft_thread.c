/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:00 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/28 01:49:07 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_thread(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo));
	// if (!philo)
		// ft_end("Philo creation failed", data, 1);
	data->philo = philo;
	while (++i < data->nb_philo)
	{
		if (i < data->nb_philo - 1)
		{
			philo->right = (t_philo *)malloc(sizeof(t_philo));
			// if (!philo->right)
				// ft_end("Philo creation failed", data, 2);
		}
		philo->id = i + 1;
		if (i == (data->nb_philo - 1) && data->nb_philo != 1)
			philo->right = data->philo;
		if (data->nb_philo != 1)
		{
			philo->right->left = philo;
			philo = philo->right;
		}
	}
}

void	ft_thread_create(t_data *data)
{
	int	i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;// pair
	while (i < data->nb_philo)
	{
		cur->data = data;
		// pthread_mutex_init(&(cur->fork), NULL);
		if (pthread_create(&(cur->thread), NULL, &routine, (void *)cur) != 0)
			return ;// ft_end("Thread didn't create\n", 4, data);
		cur = cur->right->right;
		i += 2;
	}
	cur = data->philo->right;// impair
	i = 1;
	while (i < data->nb_philo)
	{
		cur->data = data;
		// pthread_mutex_init(&(cur->fork), NULL);
		if (pthread_create(&(cur->thread), NULL, &routine, (void *)cur) != 0)
			return ;// ft_end("Thread didn't create\n", 4, data);
		cur = cur->right->right;
		i += 2;
	}
}

void	ft_thread_end(t_data *data)
{
	int	i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;
	while (i < data->nb_philo)
	{
		pthread_join(cur->thread, NULL);
		// if ( != 0)
		// 	ft_end("Thread didn't stop\n", 5, data);
		// pthread_mutex_destroy(&(cur->fork));
		cur = cur->right;
		i++;
	}
}

void	ft_thread(t_data *data)
{
	ft_thread_create(data);
	ft_thread_end(data);
}
