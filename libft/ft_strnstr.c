/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:51:45 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:26:53 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (!haystack || !needle)
		return (0);
	if (!needle[0])
		return ((char *)haystack);
	if (!len)
		return (0);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (!needle[j + 1] && i + j < len)
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (0);
}
