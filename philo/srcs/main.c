/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:37:22 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/24 02:01:26 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(struct timeval *debut)
{
	struct timeval	fin;

	gettimeofday(&fin, NULL);
	// return (((&fin)->tv_sec - debut->tv_sec)
	// 	+ ((&fin)->tv_usec - debut->tv_usec));
	printf("%f\n", (1e-3 * ((&fin)->tv_sec - debut->tv_sec)));
	printf("%f\n", (1e3 * ((&fin)->tv_usec - debut->tv_usec)));

	return ((1e-3 * ((&fin)->tv_sec - debut->tv_sec))
		+ (1e3 * ((&fin)->tv_usec - debut->tv_usec)));
}

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
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (!printf("./philo nb_philo die eat sleep [nb_eat]\n"));
	if (!ft_checkarg(argv))
		return (!printf("Error\n"));
	ft_init(&data, argc, argv);
	// printf("%d\n", gettimeofday(&debut, NULL));
	usleep(40000);
	// printf("%d\n", gettimeofday(&fin, NULL));
	printf("%d\n", get_time(&data.time));
	// printf("coucou %s\n", argv[0]);
}
