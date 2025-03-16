/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:19:12 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/16 20:54:49 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	de_sync_phils(t_phil *phil)
{
	if (phil->tab->phil_nbr)
	{
		if (!(phil->id % 2))
			precise_usleep(3e4, phil->tab);
	}
	else
		if (phil->id % 2)
			thinking(phil, true);
}

bool	cant_create(t_tab *tab, int i)
{
	if (tab->phil_nbr == 1)
	{
		if (safe_thr_handle(&tab->phils[0].thread_id, \
					lone_phil, &tab->phils[0], CREATE))
			return (true);
	}
	else
		while (++i < tab->phil_nbr)
			if (safe_thr_handle(&tab->phils[i].thread_id, \
						dinner_sim, &tab->phils[i], CREATE))
				return (true);
	return (false);
}

static bool	phil_died(t_phil *phil)
{
	long	ela;
	long	ttd;

	if (get_bool(&phil->phil_mtx, &phil->full))
		return (false);
	ela = gettime(MILLISECOND) - get_long(&phil->phil_mtx, &phil->lmt);
	ttd = phil->tab->ttd / 1e3;
	if (ela > ttd)
		return (true);
	return (false);
}

static bool	all_threads_full(t_tab *tab)
{
	int		i;
	t_phil	*phil;

	i = -1;
	while (++i < tab->phil_nbr)
	{
		phil = tab->phils + i;
		if (get_bool(&phil->phil_mtx, &phil->full))
			return (true);
	}
	return (false);
}

void	*butler(void *data)
{
	t_tab	*tab;
	int		i;

	tab = (t_tab *)data;
	while (!all_threads_running(&tab->tab_mtx, &tab->trn, \
				tab->phil_nbr))
		;
	while (!sim_fin(tab) && all_threads_full(tab))
	{
		i = -1;
		while (++i < tab->phil_nbr && !sim_fin(tab) && \
				all_threads_full(tab))
		{
			if (phil_died(tab->phils + i))
			{
				set_bool(&tab->tab_mtx, &tab->end_sim, true);
				write_status(DIED, tab->phils + i);
			}
		}
	}
	return (NULL);
}
