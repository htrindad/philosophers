/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:19:12 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 18:22:52 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	de_sync_phils(t_phil *phil)
{
	if (phil->tab->phil_nbr)
		if (!(phil->id % 2))
			precise_usleep(3e4, phil->tab);
	else
		if (phil->id % 2)
			thinking(phil, true);
}
