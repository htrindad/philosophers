/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:38:13 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 19:44:14 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*mon_din(void *data)
{
	t_tab	*tab;
	int		i;
	
	tab = (t_tab *)data;
	while (!all_threads_running(&tab->tab_mtx, &tab->trn, \
				tab->phil_nbr))
		;
	while (!sim_fin(tab))
	{
		i = -1;
		while (++i < tab->phils_nbr)
			if () // TODO Phil_died
	}
	return (NULL);
}
