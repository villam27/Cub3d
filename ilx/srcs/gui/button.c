/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:58:00 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/16 12:46:00 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_button	*ilx_create_button(int x, int y, int width, int height)
{
	t_button	*button;

	button = malloc(sizeof(t_button));
	if (!button)
		return (NULL);
	button->rect.x = x;
	button->rect.y = y;
	button->rect.width = width;
	button->rect.height = height;
	return (button);
}

void	ilx_background_button_color(t_button *button, uint32_t default_c,
				uint32_t under_cursor, uint32_t clicked)
{
	button->default_background = default_c;
	button->clicked_background = clicked;
	button->under_cursor_background = under_cursor;
}

void	ilx_label_button_color(t_button *button, uint32_t default_c,
				uint32_t under_cursor, uint32_t clicked)
{
	button->default_label = default_c;
	button->clicked_label = clicked;
	button->under_cursor_label = under_cursor;
}

void	ilx_add_button_label(t_button *button, char *label)
{
	button->label = ft_strdup(label);
}
