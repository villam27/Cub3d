/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:43:54 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:28:19 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *str, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (str[i] && i < dstsize)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	sdst;
	size_t	ssrc;

	if (src && dst)
	{
		ssrc = ft_strlen(src);
		sdst = ft_strnlen(dst, dstsize);
		if (dstsize <= sdst)
			return (dstsize + ssrc);
	}
	if (!dstsize)
		return (ssrc);
	i = 0;
	while (i < ssrc && sdst + i < dstsize - 1)
	{
		dst[i + sdst] = src[i];
		i++;
	}
	dst[i + sdst] = '\0';
	if (sdst > dstsize)
		return (ssrc + dstsize);
	return (sdst + ssrc);
}
