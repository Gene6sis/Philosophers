/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:52:53 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/04 03:53:24 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void ft_destroylist(t_philo *philo, int nb)
{
	t_philo *cur;
	t_philo *next;
	int		i;

	i = 0;
	cur = philo;
	while (i < nb)
	{
		if (i + 1 < nb)
			next = cur->right;
		free(cur);
		if (i + 1 < nb)
			cur = next;
		i++;
	}
}

void	ft_error(t_data *data, int error)
{
	if (error >= 2)
		ft_destroylist(data->philo, data->nb_philo);
	if (error >= 3)
	{
		pthread_mutex_destroy(&(data->print));
	}
}

void	ft_end(char *message, t_data *data, int error)
{
	data->error = 1;
	// printf("%s\n", message);
	(void)message;
	ft_error(data, error);
}