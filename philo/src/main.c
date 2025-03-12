/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:12:48 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 18:16:49 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	clean(t_tab *tab)
{
	t_phil	*phil;
	int		i;

	i = -1;
	while (++i < tab->phil_nbr)
	{
		phil = tab->phil + 1;
		safe_mtx_handle(&phil->phil_mtx, DESTROY);
	}
	safe_mtx_handle(&tab->tab_mtx, DESTROY);
	free(tab->forks);
	free(tab->phil);
	return (-1);
}

int	main(int ac, char **av)
{

}
