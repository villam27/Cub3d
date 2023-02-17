/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:00:29 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:08:28 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	long	num;
	int		i;

	if (n < 0)
	{
		num = -n;
		i = 2;
	}
	else
	{
		num = n;
		i = 1;
	}
	while (num / 10)
	{
		i++;
		num /= 10;
	}
	return (i + 1);
}

static char	*ft_fill(int size, char *number, long num)
{
	int	i;

	if (number[0] == '-')
		i = 1;
	else
		i = 0;
	number[size] = 0;
	while (size > i)
	{
		size--;
		number[size] = num % 10 + 48;
		num /= 10;
	}
	return (number);
}

char	*ft_itoa(int n)
{
	int		size;
	long	num;
	char	*number;

	size = ft_get_size(n);
	number = malloc(sizeof(char) * size);
	if (!number)
		return (0);
	num = n;
	if (n < 0)
	{
		num *= -1;
		number[0] = '-';
	}
	size--;
	number = ft_fill(size, number, num);
	return (number);
}
