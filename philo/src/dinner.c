/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/11 18:11:36 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

static int	thinking(t_phil *phil)
{
	return (write_status(THINKING, phil));
}

void	*lone_phil(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	wait_all_threads(phil->tab);
	set_long(&phil->phil_mtx, &phil->lmt, gettime(MILLISECOND));
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
	phil->meals_count++;
	if (write_status(EATING, phil))
		return (-1);
	precise_usleep(phil->tab->tte, phil->tab);
	if (phil->tab->nlm > 0 && phil->meals_counter == phil->tab->nlm)
		if (set_bool(&phil->phil_mtx, &phil->full, true) || \
				safe_mtx_handle(&phil->r_fork, UNLOCK) || \
				safe_mtx_handle(&phil->l_fork, UNLOCK))
			return (-1);
	return (0);
}

int	dinner_start(t_tab *tab)
{
	int	i;

	i = -1;
	if (tab->nlm)
		return (0);
	else if (tab->phil_nbr == 1)
		if (safe_thr_handle(&tab->phils[0]->thread_id, \
					lone_phil, &tab->phils[0], CREATE))
			return (-1);
	else
		while (++i < tab->phil_nbr)
			if (safe_thr_handle(&tab->phils[i].thread_id, \
						dinner_sim, &tab->phils[i], CREATE))
				return (-1);
	if (safe_thr_handle(&tab->mon, mon_din, tab, CREATE))
		return (-1);
	tab->start_sim = gettime(MILLISECOND);
	if (set_bool(&tab->tab_mtx, &tab->atr, true))
		return (-1);
	i = -1;
	while (++i < tab->phil_nbr)
		if (safe_thr_handle(&tab->phils[i].thread_id, NULL, NULL, JOIN))
			return (-1);
	return (0);
}
