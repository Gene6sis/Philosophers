/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:04:55 by adben-mc          #+#    #+#             */
/*   Updated: 2022/03/04 04:20:30 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

struct	s_data;

typedef struct s_philo {
	int					id;
	pthread_mutex_t		fork;//
	struct s_data		*data;
	pthread_t			thread;
	pthread_mutex_t		last_eat;//
	int					last_eat_time;
	int					nb_eat;
	struct s_philo		*left;
	struct s_philo		*right;
}				t_philo;

typedef struct s_manager {
	struct s_data		*data;
	pthread_t			thread;
}				t_manager;

typedef struct s_data {
	int					nb_philo;
	int					dead_time;
	int					eat_time;
	int					sleep_time;
	int					have_to_eat;
	int					error;
	struct timeval		time;
	pthread_mutex_t		print;//
	pthread_mutex_t		status_m;
	int					status;
	pthread_mutex_t		eat_m;
	int					total_eat;
	int					argc;
	char				**argv;
	t_manager			*manager;
	t_philo				*philo;
}				t_data;

/*	|||||||||||||| 	 ERROR || FREE	 |||||||||||	*/
int		ft_checkarg(char **argv);
void	ft_end(char *message, t_data *data, int error);

/*	||||||||||||||	 	PARSING		 |||||||||||	*/
int		ft_atolcheck(char *str, long max, long min);
int		ft_have_nb(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_checkarg(char **argv);

/*	|||||||||||||| 	 	ROUTINE		 |||||||||||	*/
void	*routine(void *p);
void	ft_manager(t_data *data);

/*	|||||||||||||| 	 	THREAD		 |||||||||||	*/
void	ft_init_thread(t_data *data);
void	ft_thread(t_data *data);
void	ft_thread_end(t_data *data, int pos);
void	ft_thread_create(t_data *data);

/*	|||||||||||||| 		 UTILS		 |||||||||||	*/
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
int		get_time(struct timeval *debut);
void	ft_sleep(int time, t_data *data);
int		ft_checkdead(t_data *data);
void	ft_output(int x, t_philo *philo);

#endif
