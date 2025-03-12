/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:08:34 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 18:29:52 by htrindad         ###   ########.fr       */
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
# include <string.h>

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
	t_mtx		phil_mtx;
	t_tab		*tab;
}		t_phil;

typedef struct s_tab
{
	long		phil_nbr;
	long		ttd;
	long		tte;
	long		tts;
	long		nlm;
	long		start_sim;
	long		trn;
	bool		end_sim;
	bool		atr;
	t_mtx		tab_mtx;
	t_mtx		write_mtx;
	pthread_t	mon;
	t_fork		*forks;
	t_phil		*phils;
}		t_tab;

// functions

long	ft_atol(const char *nbr);
int		safe_mtx_handle(t_mtx *mtx, t_opcode opc);
int		safe_thr_handle(pthread_t *thr, void *(*f) (void *), \
	void *data, t_opcode opc);
int		write_status(t_status stat, t_phil *phil);
long	gettime(t_time_code tc);
long	get_long(t_mtx *mtx, long *value);
bool	get_bool(t_mtx *mtx, bool *value);
void	set_long(t_mtx *mtx, long *dest, long value);
void	set_bool(t_mtx *mtx, bool *dest, bool value);
bool	sim_fin(t_tab *tab);
int		data_init(t_tab *tab);
int		write_status(t_status stat, t_phil *phil);
void	wait_all_threads(t_tab *tab);
void	precise_usleep(long usec, t_tab *tab);
void	*lone_phil(void *arg);
bool	all_threads_running(t_mtx *mtx, long *thr, long phil_nbr);
int		increase_long(t_mtx *mtx, long *val);
int		thinking(t_phil *phil);
void	de_sync_philos(t_phil *phil);
void	*dinner_sim(void *data);

#endif
