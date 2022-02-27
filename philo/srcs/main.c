/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:37:22 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/27 19:57:33 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(struct timeval *debut)
{
	struct timeval	fin;

	gettimeofday(&fin, NULL);
	return ((1e3 * ((&fin)->tv_sec - debut->tv_sec))
		+ (1e-3 * ((&fin)->tv_usec - debut->tv_usec)));
}

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
	ft_init_thread(data);
	data->status = 0;
}

void	*routine(void *p)
{
	// printf("data previous\t : %d\n", data->status);
	pthread_mutex_lock(&(((t_philo *)p)->data->fork));
	((t_philo *)p)->data->status += 1;
	pthread_mutex_unlock(&(((t_philo *)p)->data->fork));
	// printf("data after\t : %d\n", data->status);
	// printf("fork : %p\n", &(data->fork));
	// printf("philo : %d\n", philo->id);
	return (0);
}

void	ft_thread(t_data *data)
{
	int	i;
	t_philo	*cur;

	i = 0;
	cur = data->philo;
	pthread_mutex_init(&(data->fork), NULL);
	while (i < data->nb_philo)
	{
		cur->data = data;
		pthread_create(&(cur->thread), NULL, &routine, (void *)cur);
		// if ( != 0)
		// 	ft_end("Thread didn't create\n", 4, data);
		cur = cur->right;
		i++;
	}
	i = 0;
	cur = data->philo;
	while (i < data->nb_philo)
	{
		pthread_join(cur->thread, NULL);
		// if ( != 0)
		// 	ft_end("Thread didn't stop\n", 5, data);
		cur = cur->right;
		i++;
	}
	pthread_mutex_destroy(&(data->fork));
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
	printf("status : %d\n", data.status);
	// printphilo(&data);
}
