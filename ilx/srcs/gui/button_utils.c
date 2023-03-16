/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:23:44 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/16 12:49:28 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static int	ft_cp_button(t_button *src, t_button *dest)
{
	dest->rect = src->rect;
	dest->label = ft_strdup(src->label);
	free(src->label);
	if (!dest->label)
		return (free (dest), 0);
	dest->f = src->f;
	dest->clicked_background = src->clicked_background;
	dest->default_background = src->default_background;
	dest->under_cursor_background = src->under_cursor_background;
	dest->clicked_label = src->clicked_label;
	dest->default_label = src->default_label;
	dest->under_cursor_label = src->under_cursor_label;
	dest->current_color = src->default_background;
	dest->current_label_color = src->default_label;
	return (1);
}

uint8_t	ilx_mouse_in_button(t_button *button, int x, int y)
{
	if (x >= (int)button->rect.x
		&& x <= (int)(button->rect.width + button->rect.x)
		&& y >= (int)button->rect.y
		&& y <= (int)(button->rect.height + button->rect.y))
		return (1);
	return (0);
}

int	ilx_add_button(t_gui *gui, t_button *add_button, void *(*func)(void *))
{
	int			i;
	t_button	*new_buttons;

	i = 0;
	if (gui->buttons)
		while (gui->buttons[i].label)
			i++;
	i += 2;
	new_buttons = malloc(sizeof(t_button) * i);
	if (!new_buttons)
		return (0);
	i = 0;
	if (gui->buttons)
	{
		i = -1;
		while (gui->buttons[++i].label)
			ft_cp_button(&gui->buttons[i], &new_buttons[i]);
	}
	if (!ft_cp_button(add_button, &new_buttons[i]))
		return (free(add_button), 0);
	free(add_button);
	new_buttons[i].f = func;
	new_buttons[i + 1].label = NULL;
	free(gui->buttons);
	return (gui->buttons = new_buttons, 1);
}
