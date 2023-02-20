/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:54:05 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:12:20 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(va_list *lst)
{
	char	c;

	c = va_arg(*lst, int);
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(va_list *lst)
{
	char	*s;
	int		i;

	i = 0;
	s = va_arg(*lst, char *);
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_ptr(va_list *lst)
{
	void	*ptr;
	char	*str;
	int		i;

	i = 0;
	ptr = va_arg(*lst, void *);
	str = ft_dec2hex_ul((unsigned long long)ptr, "0123456789abcdef");
	write(1, "0x", 2);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	free(str);
	return (i + 2);
}

int	ft_print_signed_i(va_list *lst)
{
	int	n;
	int	i;

	i = 0;
	n = va_arg(*lst, int);
	ft_putnbr(n, &i);
	if (n < 0)
		i++;
	return (i);
}
