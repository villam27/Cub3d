/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:41:41 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/07 13:42:05 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_textured_button	*ilx_create_tex_button(int x, int y, char *label, t_ilx_texture *tex_ptr)
{
	t_textured_button	*button;

	button = malloc(sizeof(t_textured_button));
	button->pos.x = x;
	button->pos.y = y;
	button->label = ft_strdup(label);
	if (!button->label)
		return (free(button), NULL);
	button->text_ptr = tex_ptr;
	return (button);
}

void	ilx_set_tex_button_rects(t_textured_button *button, t_rectangle def, t_rectangle under, t_rectangle click)
{
	button->default_rect = def;
	button->default_tex_pos = def;
	button->under_tex_pos = under;
	button->clicked_tex_pos = click;
}

void	ilx_set_tex_button_datas(t_textured_button *button, size_t step, uint32_t speed)
{
	button->under_steps = step;
	button->speed = speed;
}

void	ilx_draw_tex_button(t_window *win, t_textured_button *button)
{
	ilx_render_copy(win, button->text_ptr, &button->pos, &button->default_rect);
}
