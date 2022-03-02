/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 00:52:53 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/02 03:37:49 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_error(t_data *data, int error)
{
	(void)data;
	(void)error;
}

void	ft_end(char *message, t_data *data, int error)
{
	(void)message;
	ft_error(data, error);
}