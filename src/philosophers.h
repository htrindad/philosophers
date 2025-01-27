/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:41:39 by htrindad          #+#    #+#             */
/*   Updated: 2025/01/27 11:55:51 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	bool			eating;
	size_t			me;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	size_t			st;
	size_t			nop;
	size_t			notte;
	bool			*dead;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*wl;
	pthread_mutex_t	*dl;
	pthread_mutex_t	*ml;
}	t_philosopher;

typedef struct s_program
{
	bool			dead_flag;
	pthread_mutex_t	dl;
	pthread_mutex_t	ml;
	pthread_mutex_t	wl;
}	t_program;

typedef timeval	t_timeval;

size_t	ft_atoul(char *nbr);

#endif
