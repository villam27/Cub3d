/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:30:51 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:10:52 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n - 1 && ((unsigned char *)s)[i] != (unsigned char)c)
		i++;
	if (((unsigned char *)s)[i] == (unsigned char)c && n)
		return (&((char *)s)[i]);
	else
		return (0);
}
