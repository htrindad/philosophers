/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:18:15 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/17 19:40:29 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_mtx_handle(t_mtx *mtx, t_opcode opc)
{
	if (opc == LOCK)
		return (pthread_mutex_lock(mtx));
	if (opc == UNLOCK)
		return (pthread_mutex_unlock(mtx));
	if (opc == INIT)
		return (pthread_mutex_init(mtx, NULL));
	if (opc == DESTROY)
		return (pthread_mutex_destroy(mtx));
	return (0);
}

int	safe_thr_handle(pthread_t *thr, void *(*f) (void *),
		void *data, t_opcode opc)
{
	if (opc == CREATE)
		return (pthread_create(thr, NULL, f, data));
	if (opc == JOIN)
		return (pthread_join(*thr, NULL));
	if (opc == DETACH)
		return (pthread_detach(*thr));
	return (0);
}

bool	all_phils_full(t_tab *tab)
{
	t_phil	*phil;
	int		i;

	i = -1;
	while (++i < tab->phil_nbr)
	{
		phil = tab->phils + i;
		if (!get_bool(&phil->phil_mtx, &phil->full))
			return (false);
	}
	return (true);
}
