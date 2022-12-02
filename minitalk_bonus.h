/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:24:58 by nhwang            #+#    #+#             */
/*   Updated: 2022/06/16 15:42:13 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_person {
	int				index;
	unsigned char	buf;
	pid_t			si_pid;
}	t_person;

typedef struct s_listt {
	int		index;
	char	*string;
	pid_t	sv_pid;
}	t_glist;

#endif