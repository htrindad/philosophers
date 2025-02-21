/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:18:15 by htrindad          #+#    #+#             */
/*   Updated: 2025/02/21 18:15:35 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_mtx_handle(t_mtx *mtx, t_opcode opc)
{
	int	status;

	status = 0;
	if (opc == LOCK)
		status = pthread_mutex_lock(mtx);
	if (opc == UNLOCK)
		status = pthread_mutex_unlock(mtx);
	if (opc == INIT)
		status = pthread_mutex_init(mtx, NULL);
	if (opc == DESTROY)
		status = pthread_mutex_destroy(mtx);
	return (status);
}

int	safe_thr_handle(pthread_t *thr, void *(*f) (void *),
		void *data, t_opcode opc)
{
	int	status;

	status = 0;
	if (opc == CREATE)
		status = pthread_create(thr, NULL, f, data);
	if (opc == JOIN)
		status = pthread_join(*thr, NULL);
	if (opc == DETACH)
		status = pthread_detach(*thr);
	return (status);
}
