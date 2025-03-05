/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/05 17:59:52 by htrindad         ###   ########.fr       */
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
	if (set_long(&phil->phil_mtx, &phil->lmt, gettime(MILLISECOND)))
		return ((void *)-1);
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
