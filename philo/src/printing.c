/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:32:42 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/13 19:13:46 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_status(t_status stat, t_phil *phil)
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
	else if (stat == THINKING && !sim_fin(phil->tab))
		printf("%-6ld %d is thinking\n", ela, phil->id);
	else if (stat == DIED)
		printf("%-6ld %d died\n", ela, phil->id);
	return (safe_mtx_handle(&phil->tab->write_mtx, UNLOCK));
}
