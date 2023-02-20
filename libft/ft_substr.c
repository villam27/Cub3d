/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:01:53 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:27:26 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start > ft_strlen(s))
		len = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[start] && i < len && len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}
