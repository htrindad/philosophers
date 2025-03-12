/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:20:02 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 18:37:59 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_phil *phil, t_fork *fork, int phil_pos)
{
	int	phil_nbr;

	phil_nbr = phil->tab->phil_nbr;
	phil->r_fork = &fork[(phil_pos + 1) % phil_nbr];
	phil->l_fork = &fork[phil_pos];
	if (!(phil_pos % 2))
	{
		phil->r_fork = &fork[phil_pos];
		phil->l_fork = &fork[(phil_pos + 1) % phil_nbr];
	}
}

static int	philo_init(t_tab *tab)
{
	t_phil	*phil;
	int		i;
	int		fs;

	i = -1;
	fs = 0;
	while (++i < tab->phil_nbr)
	{
		phil = tab->phils;
		phil->id = i + 1;
		phil->full = false;
		phil->meals_count = 0;
		phil->tab = tab;
		fs = safe_mtx_handle(&phil->phil_mtx, INIT);
		if (fs)
			return (fs);
		assign_forks(phil, tab->forks, i);
	}
}

int	data_init(t_tab *tab)
{
	int	i;

	i = -1;
	tab->end_sim = false;
	tab->atr = false;
	if (safe_mtx_handle(tab->tab_mtx, INIT))
		return (-1);
	tab->atr = false;
	tab->trn = 0;
	tab->phils = malloc(sizeof(t_phil) * tab->phil_nbr);
	tab->forks = malloc(sizeof(t_fork) * tab->phil_nbr);
	if (tab->phils == NULL || tab->forks == NULL \
			|| safe_mtx_handle(&tab->mtx, INIT) || \
			safe_mtx_handle(&tab->write_mtx, INIT))
		return (-1);
	while (++i < tab->phil_nbr)
	{
		if (safe_mtx_handle(&tab->forks[i].fork, INIT))
			return (-1);
		tab->forks[i].fork_id = i;
	}
	philo_init(tab);
	return (0);
}
