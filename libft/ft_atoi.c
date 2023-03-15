/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:09:40 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/15 20:14:13 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	m;

	i = 0;
	m = 1;
	n = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		errno = 42;
	n *= m;
	return (n);
}
