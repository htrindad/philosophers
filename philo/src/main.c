/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:12:48 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/16 19:12:16 by htrindad         ###   ########.fr       */
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
		phil = tab->phils + i;
		safe_mtx_handle(&phil->phil_mtx, DESTROY);
	}
	safe_mtx_handle(&tab->tab_mtx, DESTROY);
	if (tab->forks)
		free(tab->forks);
	if (tab->phils)
		free(tab->phils);
	return (-1);
}

static inline bool	error_check(t_tab *tab)
{
	if (tab->phil_nbr == -1 || tab->ttd == -1 || \
			tab->tte == -1 || tab->tts == -1 || \
			!tab->phil_nbr)
		return (true);
	return (false);
}

static int	parse_input(t_tab *tab, char **av)
{
	tab->phil_nbr = ft_atol(av[1]);
	tab->ttd = ft_atol(av[2]) * 1e3;
	tab->tte = ft_atol(av[3]) * 1e3;
	tab->tts = ft_atol(av[4]) * 1e3;
	if (tab->ttd < 6e4 || tab->tte < 6e4 || \
			tab->tts < 6e4 || error_check(tab))
		return (-1);
	if (av[5])
	{
		tab->nlm = ft_atol(av[5]);
		if (tab->nlm == -1)
			return (-1);
	}
	else
		tab->nlm = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_tab	tab;

	if ((ac != 5 && ac != 6) || \
			parse_input(&tab, av))
		return (-1);
	if (data_init(&tab) || dinner_start(&tab))
		return (clean(&tab));
	clean(&tab);
	return (0);
}
