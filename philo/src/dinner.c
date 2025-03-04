/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:03:30 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/04 20:43:24 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

static int	write_status(t_status stat, t_phil *phil)
{
	long	ela;

	ela = gettime(MILLISECOND) - phil->tab->start_sim;
	if (phil->full)
		return (0);
	if (safe_mtx_handle(&phil->tab->write_mtx, LOCK))
		return (-1);
	if ((stat == TAKE_RIGHT_FORK || stat == TAKE_LEFT_FORK) \
			&& !sim_fin(phil->tab))
		printf("%-6ld %d has taken a fork\n", ela, phil->id);
	else if (stat == EATING && !sim_fin(phil->tab))
		printf("%-6ld %d is eating\n", ela, phil->id);
	else if (stat == SLEEPING && !sim_fin(phil->tab))
		printf("%-6ld %d is sleeping\n", ela, phil->id);
	else if (stat == THINKING && !simfin(phil->tab))
		printf("%-6ld %d is thinking\n", ela, phil->id);
	else if (stat == DIED)
		printf("%-6ld %d died\n", ela, phil->id);
	return (safe_mtx_handle(&phil->tab->write_mtx, UNLOCK));
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
