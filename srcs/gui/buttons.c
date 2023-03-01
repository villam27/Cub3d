/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:10:04 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 11:33:18 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"
#include "cub3D.h"

static void	in_button(t_data *data, int i)
{
	data->current_gui->buttons[i].current_color
		= data->current_gui->buttons[i].under_cursor_background;
	data->current_gui->buttons[i].current_label_color
		= data->current_gui->buttons[i].under_cursor_label;
}

void	ilx_change_button_color(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	if (!data->current_gui)
		return ;
	mlx_mouse_get_pos(data->ilx->mlx, data->ilx->window->window, &x, &y);
	while (data->current_gui->buttons[i].label)
	{
		if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			return (in_button(data, i));
		else if (data->current_gui->buttons[i].current_color
			== data->current_gui->buttons[i].under_cursor_background)
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].default_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].default_label;
		}
		i++;
	}
}
