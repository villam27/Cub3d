/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:25:39 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 12:53:41 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "key_binding.h"

int	on_clic(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == RIGHT_CLICK)
	{
		if (!data->current_gui)
			data->current_gui = data->gui;
		else
			data->current_gui = NULL;
	}
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

int	on_release(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == LEFT_CLICK && data->current_gui)
	{
		data->clic = 0;
		while (data->current_gui->buttons[i].label)
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].default_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].default_label;
			i++;
		}
		i = 0;
		while (data->current_gui->buttons[i].label)
		{
			if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			{
				(*data->current_gui->buttons[i].f)(data);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	ft_press_key(int keycode, t_data *data)
{
	if (keycode == RIGHT)
		data->key_tab[0] = 1;
	else if (keycode == LEFT)
		data->key_tab[1] = 1;
	else if (keycode == W)
		data->key_tab[2] = 1;
	else if (keycode == S)
		data->key_tab[3] = 1;
	else if (keycode == A)
		data->key_tab[4] = 1;
	else if (keycode == D)
		data->key_tab[5] = 1;
	return (0);
}

int	ft_up_key(int keycode, t_data *data)
{
	if (keycode == RIGHT)
		data->key_tab[0] = 0;
	else if (keycode == LEFT)
		data->key_tab[1] = 0;
	else if (keycode == W)
		data->key_tab[2] = 0;
	else if (keycode == S)
		data->key_tab[3] = 0;
	else if (keycode == A)
		data->key_tab[4] = 0;
	else if (keycode == D)
		data->key_tab[5] = 0;
	return (0);
}
