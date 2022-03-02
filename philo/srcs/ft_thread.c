/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:00 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/02 04:20:09 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_thread(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (ft_end("Philo creation failed", data, 1));
	data->philo = philo;
	while (++i < data->nb_philo)
	{
		if (i < data->nb_philo - 1)
		{
			philo->right = (t_philo *)malloc(sizeof(t_philo));
			if (!philo->right)
			{
				philo->right = NULL;
				return (ft_end("Philo creation failed", data, 2));
			}
		}
		philo->id = i + 1;
		if (i == (data->nb_philo - 1) && data->nb_philo)
			philo->right = data->philo;
		if (data->nb_philo)
		{
			philo->right->left = philo;
			philo = philo->right;
		}
	}
}

void	ft_thread_create_pair(t_data *data)
{
	int		i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;// pair
	while (i < data->nb_philo)
	{
		cur->data = data;
		pthread_mutex_init(&(cur->fork), NULL);
		if (pthread_create(&(cur->thread), NULL, &routine, (void *)cur) != 0)
		{
			ft_thread_end_pair(data, i);
			return (ft_end("Thread impair didn't create\n", data, 4));
		}
		cur = cur->right->right;
		i += 2;
	}
}

void	ft_thread_create_impair(t_data *data)
{
	int		i;
	t_philo	*cur;

	cur = data->philo->right;// impair
	i = 1;
	while (i < data->nb_philo)
	{
		cur->data = data;
		pthread_mutex_init(&(cur->fork), NULL);
		if (pthread_create(&(cur->thread), NULL, &routine, (void *)cur) != 0)
		{
			ft_thread_end_pair(data, data->nb_philo);
			ft_thread_end_impair(data, i);
			return (ft_end("Thread impair didn't create\n", data, 5));
		}
		cur = cur->right->right;
		i += 2;
	}
}

void	ft_thread_end_pair(t_data *data, int pos)
{
	int		i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;
	while (i < pos)
	{
		if (pthread_join(cur->thread, NULL) != 0)
			return (ft_end("Thread didn't stop\n", data, 5));
		pthread_mutex_destroy(&(cur->fork));
		cur = cur->right->right;
		i += 2;
	}
}

void	ft_thread_end_impair(t_data *data, int pos)
{
	int		i;
	t_philo	*cur;

	i = 1;
	cur = data->philo->right;
	while (i < pos)
	{
		if (pthread_join(cur->thread, NULL) != 0)
			return (ft_end("Thread didn't stop\n", data, 5));
		pthread_mutex_destroy(&(cur->fork));
		cur = cur->right->right;
		i += 2;
	}
}

void	ft_thread(t_data *data)
{
	if (!data->error)
		ft_thread_create_pair(data);
	if (!data->error)
		ft_thread_create_impair(data);
	if (!data->error)
		ft_thread_end_pair(data, data->nb_philo);
	if (!data->error)
		ft_thread_end_impair(data, data->nb_philo);
}
