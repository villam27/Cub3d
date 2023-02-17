/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:45:35 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/05 17:10:57 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rverse_str(char *str, int size)
{
	int	i;
	int	tmp;
	int	j;

	i = 0;
	j = size - 1;
	while (i < size / 2)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

int	ft_bad_base_atoi(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		i++;
	}
	i = 0;
	while (base[i])
	{
		j = 0;
		while (base[j])
		{
			if (i != j && base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_in_base(char *base, char c)
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

int	ft_num_from_base(char *str, char *base, int i)
{
	int	size_base;
	int	size_str;
	int	n;
	int	b;

	n = 0;
	size_base = ft_strlen(base);
	size_str = ft_strlen(str);
	while (str[i] && ft_in_base(base, str[i]))
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
