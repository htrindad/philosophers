/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:02:03 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/03 20:18:02 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	if (safe_mtx_handle(mtx, LOCK))
		return (-1);
	*dest = value;
	return (safe_mtx_handle(mtx, UNLOCK));
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mtx_handle(mtx, LOCK);
	ret = *value;
	safe_mtx_handle(mtx, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mtx_handle(mtx, LOCK);
	ret = *value;
	safe_mtx_handle(mtx, UNLOCK);
	return (ret);
}

int	set_long(t_mtx *mtx, long *dest, long value)
{
	if (safe_mtx_handle(mtx, LOCK))
		return (-1);
	*dest = value;
	return (safe_mtx_handle(mtx, UNLOCK));
}

bool	sim_fin(t_tab *tab)
{
	return (get_bool(&tab->tab_mtx, &tab->end_sim));
}
