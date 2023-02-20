/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:11:12 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:08:54 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*needle;

	if (!lst || !new)
		return ;
	needle = *lst;
	if (!needle)
	{
		(*lst) = new;
		return ;
	}
	while (needle->next)
		needle = needle->next;
	needle->next = new;
}
