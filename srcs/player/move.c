/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:03:45 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 11:25:06 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate(int x, int y, t_data *data)
{
	(void)y;
	if (!data->current_gui)
	{
		if (x < data->prev_x)
			data->player->angle += (0.002f * (data->prev_x - x));
		if (x > data->prev_x)
			data->player->angle -= (0.002f * (x - data->prev_x));
	}
	data->prev_x = x;
	return (0);
}

int	move_mouse(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->current_gui)
	{
		data->prev_x = data->ilx->window->win_width >> 1;
		mlx_mouse_move(data->ilx->mlx, data->ilx->window->window,
			data->ilx->window->win_width >> 1,
			data->ilx->window->win_height >> 1);
	}
	return (0);
}

void	move(t_data *data, float val, float angle_off)
{
	float	x_step;
	float	y_step;
	float	x_offset;
	float	y_offset;

	x_step = data->player->pos.x + sinf(data->player->angle + angle_off) * val;
	y_step = data->player->pos.y + cosf(data->player->angle + angle_off) * val;
	if (x_step < data->player->pos.x)
		x_offset = -0.17f;
	else
		x_offset = 0.17f;
	if (y_step < data->player->pos.y)
		y_offset = -0.17f;
	else
		y_offset = 0.17f;
	if (!data->map[((int)(y_step + y_offset))][((int)
		(data->player->pos.x + x_offset))]
		&& !data->map[((int)(y_step + y_offset))]
		[((int)(data->player->pos.x - x_offset))])
		data->player->pos.y = y_step;
	if (!data->map[((int)(data->player->pos.y + y_offset))]
		[((int)(x_step + x_offset))]
		&& !data->map[((int)(data->player->pos.y - y_offset))]
		[((int)(x_step + x_offset))])
		data->player->pos.x = x_step;
}

void	move_player(t_data *data, float delta)
{
	if (data->key_tab[0] == 1)
		data->player->angle -= data->player->rotation_speed * delta;
	else if (data->key_tab[1] == 1)
		data->player->angle += data->player->rotation_speed * delta;
	if (data->key_tab[2] && data->key_tab[4])
		return (move(data, data->player->player_speed / 2.0f * delta, 0.0f),
			move(data, data->player->player_speed / 2.0f * delta, M_PI_2));
	if (data->key_tab[2] && data->key_tab[5])
		return (move(data, data->player->player_speed / 2.0f * delta, 0.0f),
			move(data, -data->player->player_speed / 2.0f * delta, M_PI_2));
	if (data->key_tab[3] && data->key_tab[4])
		return (move(data, -data->player->player_speed / 2.0f * delta, 0.0f),
			move(data, data->player->player_speed / 2.0f * delta, M_PI_2));
	if (data->key_tab[3] && data->key_tab[5])
		return (move(data, -data->player->player_speed / 2.0f * delta, 0.0f),
			move(data, -data->player->player_speed / 2.0f * delta, M_PI_2));
	if (data->key_tab[2] == 1)
		move(data, data->player->player_speed * delta, 0.0f);
	if (data->key_tab[3] == 1)
		move(data, -data->player->player_speed * delta, 0.0f);
	if (data->key_tab[4] == 1)
		move(data, data->player->player_speed * delta, M_PI_2);
	if (data->key_tab[5] == 1)
		move(data, -data->player->player_speed * delta, M_PI_2);
}
