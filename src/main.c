/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:56:17 by htrindad          #+#    #+#             */
/*   Updated: 2025/02/03 14:10:10 by htrindad         ###   ########.fr       */
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
		philo[i].id = i;
		philo[i].nop = pn;
		philo[i].st = time;
		philo[i].eating = false;
		philo[i].me = 0;
		philo[i].lm = 0;
		philo[i].ttd = ft_atoul(av[2]);
		philo[i].tte = ft_atoul(av[3]);
		philo[i].tts = ft_atoul(av[4]);
		if (ac > 5)
			philo[i].notte = ft_atoul(av[5]);
		else
			philo[i].notte = 0;
		i++;
	}
	philo[pn] = NULL;
}

static size_t	set_prog(t_program *prog, t_philo *philo, int ac, char **av)
{
	size_t	pn;

	pn = ft_atoul(av[1]) + 1;
	philo = malloc(pn * sizeof(t_philosopher));
	set_data(philo, ac, av, pn);
	prog->philos = philo;
	prog->dead_flag = false;
	pthread_mutex_init(&prog->wl, NULL);
	pthread_mutex_init(&prog->dl, NULL);
	pthread_mutex_init(&prog->ml, NULL);
	return (pn);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_program		program;
	size_t			pn;

	if (ac < 5 || ac > 6)
		return (-1);
	if (philo == NULL)
		return (-1);
	pn = set_prog(&program, philo, ac, av);
	return (0);
}
