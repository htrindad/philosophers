/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:07:39 by htrindad          #+#    #+#             */
/*   Updated: 2025/01/27 10:09:38 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_atoul(char *nbr)
{
	size_t	i;
	size_t	num;

	i = 0;
	num = 0;
	while (num[i] == ' ' || num[i] == '\t')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
		num = num * 10 + nbr[i++] - '0';
	return (num);
}
