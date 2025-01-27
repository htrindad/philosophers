/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:56:17 by htrindad          #+#    #+#             */
/*   Updated: 2025/01/27 13:41:25 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_data(t_philosopher *philo, int ac, char **av, int pn)
{
	size_t		i;
	t_timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	while (i < pn)
	{
		philo.id = i;
		philo.nop = pn;
		philo.st = time;
		philo.eating = false;
		philo.me = 0;
		philo.ttd = ft_atoul(av[2]);
		philo.tte = ft_atoul(av[3]);
		philo.tts = ft_atoul(av[4]);
		if (ac > 5)
			philo.notte = ft_atoul(av[5]);
		else
			philo.notte = 0;
		i++;
	}
	philo[pn] = NULL;
}

int	main(int ac, char **av)
{
	t_philosopher	*philo;
	size_t			pn;

	if (ac < 5 || ac > 6)
		return (-1);
	pn = ft_atoul(av[1]) + 1;
	philo = malloc(pn * sizeof(t_philosopher));
	if (philo == NULL)
		return (-1);
	set_data(philo, ac, av, pn);
	return (0);
}
