/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:04:55 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/28 06:01:32 by adben-mc         ###   ########.fr       */
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
/*
	int gettimeofday(struct timeval *tv, struct timezone *tz);
	int pthread_create(pthread_t *restrict thread,
						const pthread_attr_t *restrict attr,
						void *(*start_routine)(void *),
						void *restrict arg);
	int pthread_detach(pthread_t th);
	int pthread_join(pthread_t thread, void **retval);
	int pthread_mutex_init(pthread_mutex_t *mutex, 
		const pthread_mutexattr_t *attr);
	int pthread_mutex_destroy(pthread_mutex_t *mutex);
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int pthread_mutex_lock(pthread_mutex_t *mutex);
	int pthread_mutex_unlock(pthread_mutex_t *mutex);
	void * memset( void * pointer, int value, size_t count );
*/

struct s_data;

typedef struct s_philo {
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				last_eat;
	struct s_philo	*left;
	struct s_philo	*right;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct s_data {
	int				nb_philo;
	int				eat_time;
	int				sleep_time;
	int				dead_time;
	int				have_to_eat;
	int				eat_nb;
	int				status;
	struct timeval	time;
	int				argc;
	pthread_mutex_t	print;
	char			**argv;
	t_philo			*philo;
}				t_data;

/*	|||||||||||||| 	 ERROR || FREE	 |||||||||||	*/
int		ft_checkarg(char **argv);

/*	||||||||||||||	 	PARSING		 |||||||||||	*/
int			ft_atolcheck(char *str, long max, long min);
int			ft_have_nb(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_checkarg(char **argv);

/*	|||||||||||||| 	 	ROUTINE		 |||||||||||	*/
void	*routine(void *p);

/*	|||||||||||||| 	 	THREAD		 |||||||||||	*/
void	ft_init_thread(t_data *data);
void	ft_thread(t_data *data);

/*	|||||||||||||| 		 UTILS		 |||||||||||	*/
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
void	printphilo(t_data *data);
int		get_time(struct timeval *debut);
void	ft_sleep(int time);

#endif
