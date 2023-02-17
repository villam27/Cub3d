/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 08:21:17 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:12:08 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned_i(va_list *lst)
{
	unsigned int	n;
	int				i;

	i = 0;
	n = va_arg(*lst, unsigned int);
	ft_putnbr_u(n, &i);
	return (i);
}

int	ft_print_x(va_list *lst)
{
	unsigned int	n;
	char			*num;
	int				i;

	n = va_arg(*lst, unsigned int);
	num = ft_dec2hex_u(n, "0123456789abcdef");
	ft_putstr_fd(num, 1);
	i = ft_strlen(num);
	free(num);
	return (i);
}

int	ft_print_x_up(va_list *lst)
{
	unsigned int	n;
	char			*num;
	int				i;

	n = va_arg(*lst, unsigned int);
	num = ft_dec2hex_u(n, "0123456789ABCDEF");
	ft_putstr_fd(num, 1);
	i = ft_strlen(num);
	free(num);
	return (i);
}

int	ft_switch(char c, va_list *lst)
{
	int	n;

	n = 0;
	if (c == 'c')
		n = ft_print_c(lst);
	else if (c == 's')
		n = ft_print_str(lst);
	else if (c == 'p')
		n = ft_print_ptr(lst);
	else if (c == 'd' || c == 'i')
		n = ft_print_signed_i(lst);
	else if (c == 'u')
		n = ft_print_unsigned_i(lst);
	else if (c == 'x')
		n = ft_print_x(lst);
	else if (c == 'X')
		n = ft_print_x_up(lst);
	else if (c == '%')
	{
		write(1, "%", 1);
		n = 1;
	}
	return (n);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		n;
	int		r;
	va_list	lst;

	i = 0;
	n = 0;
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			r = ft_switch(str[i + 1], &lst);
			n += r - 2;
			i++;
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	va_end(lst);
	return (i + n);
}
