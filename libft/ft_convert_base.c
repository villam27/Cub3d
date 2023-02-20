/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:01:04 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/09 13:20:59 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	n;
	int	m;

	i = 0;
	m = 1;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m *= -1;
		i++;
	}
	if (ft_in_base(base, str[i]))
		n = ft_num_from_base(str, base, i);
	else
		return (0);
	n *= m;
	return (n);
}

int	ft_bad_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if ((base[i] == '+' || base[i] == '-' ) || (base[i] < 32))
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

char	*ft_putnbr_base(int nbr, char *base, int i, int s)
{
	long int	n;
	int			size;
	char		*nbr_conv;

	nbr_conv = malloc(sizeof(char) * 100);
	size = ft_strlen(base);
	n = nbr;
	if (n < 0)
	{
		s = 1;
		n = -n;
	}
	while (n > size - 1)
	{
		nbr_conv[i] = base[n % size];
		n = n / size;
		i++;
	}
	nbr_conv[i] = base[n];
	if (s)
		nbr_conv[i + 1] = '-';
	ft_rverse_str(nbr_conv, ft_strlen(nbr_conv));
	return (nbr_conv);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		nb;
	char	*nbr_convert;

	nb = 0;
	nbr_convert = malloc(sizeof(char) * 100);
	if (ft_bad_base_atoi(base_from) || ft_strlen(base_from) < 2)
		return (0);
	if (ft_bad_base(base_to) || ft_strlen(base_to) < 2)
		return (0);
	nb = ft_atoi_base(nbr, base_from);
	nbr_convert = ft_putnbr_base(nb, base_to, 0, 0);
	return (nbr_convert);
}
