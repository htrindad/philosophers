/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:18:28 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/05 18:19:24 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code tc)
{
	t_tv	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	if (tc == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (tc == MILLISECOND)
		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	else if (tc == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (0);
}

void	wait_all_threads(t_tab *tab)
{
	while (!get_bool(&tab->tab_mtx, tab->atr))
		;
}

void	precise_usleep(long usec, t_tab *tab)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (sim_fin(tab))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
				;
	}
}

bool	all_threads_running(t_mtx *mtx, long *thr, long phil_nbr)
{
	bool	ret;

	ret = false;
	safe_mtx_handle(mtx, LOCK);
	if (*thr == phil_nbr)
		ret = true;
	safe_mtx_handle(mtx, UNLOCK);
	return (ret);
}

int	increase_long(t_mtx *mtx, long *val)
{
	if (safe_mtx_handle(mtx, LOCK))
		return (-1);
	(*val)++;
	return (safe_mtx_handle(mtx, UNLOCK));
}
