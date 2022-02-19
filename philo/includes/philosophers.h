/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:04:55 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/19 01:35:25 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data {
	char			**argv;
	int				argc;
	int				nb_number;
	int				median;
	int				max_nb;
	char			**split;
}				t_data;

/*	|||||||||||||| 	 ERROR || FREE	 |||||||||||	*/
int		ft_checkarg(char **argv);

/*	||||||||||||||	 	 PARSING	 |||||||||||	*/

/*	|||||||||||||| 	 LOCK & UNLOCK	 |||||||||||	*/

/*	|||||||||||||| 		 UTILS		 |||||||||||	*/

#endif
