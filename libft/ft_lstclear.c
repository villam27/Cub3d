/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:46:24 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:09:24 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;

	if (!lst || !del)
		return ;
	while ((*lst)->next)
	{
		l = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		(*lst) = l;
	}
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
