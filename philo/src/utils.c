/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:19:12 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 19:31:33 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	de_sync_phils(t_phil *phil)
{
	if (phil->tab->phil_nbr)
		if (!(phil->id % 2))
			precise_usleep(3e4, phil->tab);
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
				return (-1);
	}
	else
		while (++i < tab->phil_nbr)
			if (safe_thr_handle(&tab->phils[i].thread_id, \
						dinner_sim, &tab->phils[i], CREATE))
				return (true);
	return (false);
}
