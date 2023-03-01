/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_clic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:27:45 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 11:31:45 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	r_clic(t_data *data)
{
	if (!data->current_gui)
	{
		ft_memset(data->key_tab, 0, sizeof(int) * 6);
		mlx_mouse_show(data->ilx->mlx, data->ilx->window->window);
		data->current_gui = data->gui;
	}
	else
	{
		mlx_mouse_hide(data->ilx->mlx, data->ilx->window->window);
		data->current_gui = NULL;
	}
}

int	on_clic(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == RIGHT_CLICK)
		r_clic(data);
	if (key == LEFT_CLICK && data->current_gui)
	{
		data->clic = 1;
		while (data->current_gui->buttons[i].label)
		{
			if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			{
				data->current_gui->buttons[i].current_color
					= data->current_gui->buttons[i].clicked_background;
				data->current_gui->buttons[i].current_label_color
					= data->current_gui->buttons[i].clicked_label;
				return (0);
			}
			i++;
		}
	}
	return (0);
}
