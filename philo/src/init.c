/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:20:02 by htrindad          #+#    #+#             */
/*   Updated: 2025/02/21 19:25:19 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_tab *tab)
{
	int	i;

	i = -1;
	tab->end_sim = false;
	tab->atr = false;
	safe_mtx_handle(tab->tab_mtx, INIT);
}
