/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec2hex_ul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:45:46 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:07:55 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(unsigned int n)
{
	int	size;

	size = 0;
	while (n > 15)
	{
		n = n / 16;
		size++;
	}
	size += 2;
	return (size);
}

char	*ft_dec2hex_u(unsigned int n, char *base)
{
	char			*nbr_conv;
	unsigned int	number;
	int				size;
	int				i;

	i = 0;
	size = ft_get_size(n);
	number = n;
	nbr_conv = malloc(sizeof(char) * size);
	if (!nbr_conv)
		return (0);
	while (number > 15)
	{
		nbr_conv[i] = base[number % 16];
		number = number / 16;
		i++;
	}
	nbr_conv[i] = base[number];
	nbr_conv[i + 1] = 0;
	ft_rverse_str(nbr_conv, size - 1);
	return (nbr_conv);
}
