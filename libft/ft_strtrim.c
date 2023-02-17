/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:32:01 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:27:13 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_in_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	char	*ft_trim(int start, int end, const char *s1)
{
	int		i;
	int		j;
	char	*trim;

	trim = malloc(sizeof(char) * (end - start + 2));
	if (!trim)
		return (0);
	i = start;
	j = 0;
	while (i <= end)
	{
		trim[j] = s1[i];
		i++;
		j++;
	}
	trim[j] = 0;
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*trim;

	i = 0;
	while (s1[i] && ft_in_charset(s1[i], set))
		i++;
	start = i;
	if ((size_t)i == ft_strlen(s1))
	{
		start = 0;
		end = -1;
	}
	else
	{
		i = ft_strlen(s1) - 1;
		while (i >= 0 && ft_in_charset(s1[i], set))
			i--;
		end = i;
	}
	trim = ft_trim(start, end, s1);
	return (trim);
}
