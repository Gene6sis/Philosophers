/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:25:00 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 01:00:18 by adben-mc         ###   ########.fr       */
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

void	ft_thread_create(t_data *data)
{
	int		i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;
	while (i < data->nb_philo)
	{
		cur->data = data;
		pthread_mutex_init(&(cur->fork), NULL);
		cur = cur->right;
		i++;
	}
	cur = data->philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(cur->thread), NULL, &routine, (void *)cur) != 0)
		{
			ft_thread_end(data, i);
			return (ft_end("Thread impair didn't create\n", data, 4));
		}
		cur = cur->right;
		i++;
	}
}

void	ft_thread_end(t_data *data, int pos)
{
	int		i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;
	while (i < pos)
	{
		if (pthread_join(cur->thread, NULL) != 0)
			return (ft_end("Thread didn't stop\n", data, 5));
		cur = cur->right;
		i++;
	}
	i = 0;
	cur = data->philo;
	while (i < data->nb_philo)
	{
		printf("id philo : %d\n", cur->id);
		pthread_mutex_destroy(&(cur->fork));
		cur = cur->right;
		i++;
	}
}

void	ft_thread(t_data *data)
{
	if (!data->error)
		ft_thread_create(data);
	if (!data->error)
		ft_thread_end(data, data->nb_philo);
	pthread_mutex_destroy(&(data->m_status));
}
