/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:25:39 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/16 00:50:40 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	on_release(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == LEFT_CLICK && data->clic < 0)
		data->clic = 0;
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
				return ((*data->current_gui->buttons[i].f)(data), 0);
			i++;
		}
	}
	return (0);
}

int	ft_press_key(int keycode, t_data *data)
{
	if (keycode == LSHIFT)
		data->player->player_speed = data->player->sprint_speed;
	if (keycode == LCTRL)
		data->player->player_speed = data->player->sneak_speed;
	if (keycode == ESC)
		quit(data);
	if (data->current_gui)
		return (0);
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
	if ((keycode == LSHIFT
			&& data->player->player_speed == data->player->sprint_speed)
		|| (keycode == LCTRL
			&& data->player->player_speed == data->player->sneak_speed))
		data->player->player_speed = data->player->normal_speed;
	if (data->current_gui)
		return (0);
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
