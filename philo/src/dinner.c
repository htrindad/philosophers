/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/17 20:35:46 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_phil *phil, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, phil);
	if (!(phil->tab->phil_nbr % 2))
		return ;
	t_eat = phil->tab->tte;
	t_sleep = phil->tab->tts;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, phil->tab);
}

void	*lone_phil(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	wait_all_threads(phil->tab);
	set_long(&phil->phil_mtx, &phil->lmt, gettime(MILLISECOND));
	set_long(&phil->phil_mtx, &phil->tab->trn, 1);
	write_status(TAKE_RIGHT_FORK, phil);
	while (!sim_fin(phil->tab))
		usleep(100);
	return (NULL);
}

static int	eat(t_phil *phil)
{
	if (safe_mtx_handle(&phil->r_fork->fork, LOCK) || \
			write_status(TAKE_RIGHT_FORK, phil) || \
			safe_mtx_handle(&phil->l_fork->fork, LOCK) || \
			write_status(TAKE_LEFT_FORK, phil) || \
			set_long(&phil->phil_mtx, &phil->lmt, gettime(MILLISECOND)))
		return (-1);
	if (write_status(EATING, phil))
		return (-1);
	phil->meals_count++;
	precise_usleep(phil->tab->tte, phil->tab);
	if (phil->tab->nlm > 0 && phil->meals_count == phil->tab->nlm)
		if (set_bool(&phil->phil_mtx, &phil->full, true))
			return (-1);
	if (safe_mtx_handle(&phil->r_fork->fork, UNLOCK) || \
				safe_mtx_handle(&phil->l_fork->fork, UNLOCK))
		return (-1);
	return (0);
}

void	*dinner_sim(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	set_long(&phil->phil_mtx, &phil->lmt, gettime(MILLISECOND));
	increase_long(&phil->tab->tab_mtx, &phil->tab->trn);
	de_sync_phils(phil);
	while (!sim_fin(phil->tab))
	{
		if (!phil->full)
			eat(phil);
		write_status(SLEEPING, phil);
		if (phil->full)
			break ;
		precise_usleep(phil->tab->tts, phil->tab);
		thinking(phil, false);
	}
	return (NULL);
}

int	dinner_start(t_tab *tab)
{
	int	i;

	i = -1;
	tab->start_sim = gettime(MILLISECOND);
	if (!tab->nlm)
		return (0);
	else if (cant_create(tab, i))
		return (-1);
	if (safe_thr_handle(&tab->butler, butler, tab, CREATE))
		return (-1);
	if (set_bool(&tab->tab_mtx, &tab->atr, true))
		return (-1);
	while (++i < tab->phil_nbr)
		if (safe_thr_handle(&tab->phils[i].thread_id, NULL, NULL, JOIN))
			return (-1);
	return (0);
}
