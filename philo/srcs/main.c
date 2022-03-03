/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:37:22 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/03 00:58:53 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init(t_data *data, int argc, char **argv)
{
	data->argv = argv;
	data->argc = argc;
	gettimeofday(&data->time, NULL);
	data->nb_philo = ft_atoi(data->argv[1]);
	data->dead_time = ft_atoi(data->argv[2]);
	data->eat_time = ft_atoi(data->argv[3]);
	data->sleep_time = ft_atoi(data->argv[4]);
	if (data->argc == 6)
		data->have_to_eat = ft_atoi(data->argv[5]);
	else
		data->have_to_eat = -1;
	data->error = 0;
	data->status = 0;
	ft_init_thread(data);
	if (!data->error)
		pthread_mutex_init(&(data->print), NULL);
	if (!data->error)
		pthread_mutex_init(&(data->m_status), NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (!printf("./philo nb_philo die eat sleep [nb_eat]\n"));
	if (!ft_checkarg(argv))
		return (!printf("Error\n"));
	ft_init(&data, argc, argv);
	ft_thread(&data);
	if (!data.error)
		ft_end("The end", &data, 100);
}
