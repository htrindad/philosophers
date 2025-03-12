/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:29:06 by htrindad          #+#    #+#             */
/*   Updated: 2025/03/12 19:04:31 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	size_t			len;
	char const		*nbr;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (NULL);
		str++;
	}
	if (!is_digit(*str))
		return (NULL);
	nbr = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		return (NULL);
	return (nbr);
}

long	ft_atol(const char *nbr)
{
	long	num;

	num = 0;
	nbr = valid_input(nbr);
	if (nbr == NULL)
		return (-1);
	while (is_digit(*nbr))
		num = num * 10 + *nbr++ - '0';
	if (num > INT_MAX)
		return (-1);
	return (num);
}
