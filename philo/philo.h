/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:08:34 by htrindad          #+#    #+#             */
/*   Updated: 2025/02/21 16:28:29 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// imports

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

// ENUMS

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED,
}		t_status;

// typedefs

typedef pthread_mutex_t	t_mtx;
typedef struct timeval	t_tv;

// structs

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}		t_fork;

typedef struct s_phil
{
	int			id;
	long		meals_count;
	bool		full;
	long		lmt;
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	thread_id;
	t_tab		*tab;
}		t_phil;

typedef struct s_tab
{
	long		phil_nbr;
	long		ttd;
	long		tte;
	long		tts;
	long		nlm;
	bool		atr;
	t_mtx		tab_mtx;
	pthread_t	mon;
}		t_tab;

#endif
