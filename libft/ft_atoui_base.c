/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:34:15 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/05 21:34:15 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_base(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

static uint32_t	ft_num_from_base_s(char *str, char *base, int i)
{
	int			size_base;
	uint32_t	n;
	int			b;

	n = 0;
	size_base = ft_strlen(base);
	while (str[i] && ft_is_in_base(base, str[i]))
	{
		b = 0;
		while (str[i] != base[b])
			b++;
		n *= size_base;
		n += b;
		i++;
	}
	return (n);
}

uint32_t	ft_atoui_base(char *str, char *base, char *base2)
{
	int			i;
	uint32_t	n;

	i = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (ft_is_in_base(base, str[i]))
		n = ft_num_from_base_s(str, base, i);
	else if (ft_is_in_base(base2, str[i]))
		n = ft_num_from_base_s(str, base2, i);
	else
		return (0);
	return (n);
}
