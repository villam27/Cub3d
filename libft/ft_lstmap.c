/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:40 by lcrimet           #+#    #+#             */
/*   Updated: 2022/11/21 13:10:11 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*data;
	t_list	*new;
	t_list	*l;

	if (!lst || !f || !del)
		return (NULL);
	data = (*f)(lst->content);
	new = ft_lstnew(data);
	if (!new)
	{
		ft_lstclear(&l, del);
		return (NULL);
	}
	l = new;
	lst = lst->next;
	while (lst->next)
	{
		data = (*f)(lst->content);
		new->next = ft_lstnew(data);
		lst = lst->next;
		new = new->next;
	}
	data = (*f)(lst->content);
	new->next = ft_lstnew(data);
	return (l);
}
