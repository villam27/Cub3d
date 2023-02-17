/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:39:03 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/05 18:05:50 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_allocate(char *str, char *c, int cmpt, int i)
{
	int		j;
	char	**tab;

	j = 0;
	tab = malloc(sizeof(char *) * (cmpt + 1));
	if (!tab)
		return (0);
	while (str[i])
	{
		cmpt = 0;
		while (ft_is_in_str(str[i], c))
			i++;
		ft_count(str, &i, &cmpt, c);
		if (cmpt)
		{
			tab[j] = malloc(sizeof(char) * (cmpt + 1));
			if (!tab[j])
				ft_freeall(tab);
			if (!tab[j])
				return (0);
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}

static char	**ft_add_end(char **tab, int *j, int k)
{
	tab[*j][k] = 0;
	*j += 1;
	return (tab);
}

static void	ft_cpy(char *str, char *c, char **tab)
{
	int	i;
	int	j;
	int	k;
	int	n;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		n = 0;
		while (ft_is_in_str(str[i], c))
			i++;
		while (!ft_is_in_str(str[i], c) && str[i])
		{
			tab[j][k] = str[i];
			i++;
			k++;
			n++;
		}
		if (n)
			tab = ft_add_end(tab, &j, k);
	}
}

char	**ft_split(char const *str, char *c)
{
	int		i;
	int		cmpt;
	char	trigger;
	char	**tab;

	i = 0;
	cmpt = 0;
	trigger = 1;
	while (str[i])
	{
		if (trigger && !ft_is_in_str(str[i], c))
		{
			cmpt++;
			trigger = 0;
		}
		else if (!trigger && ft_is_in_str(str[i], c))
			trigger = 1;
		i++;
	}
	tab = ft_allocate((char *)str, c, cmpt, 0);
	if (!tab)
		return (0);
	ft_cpy((char *)str, c, tab);
	return (tab);
}
