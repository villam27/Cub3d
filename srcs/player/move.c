/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:03:45 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 14:10:36 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	update_player_dir(t_player *player)
{
	player->dir.x = sinf(player->angle);
	player->dir.y = cosf(player->angle);
}

void	update_player_plane(t_player *player)
{
	player->plane.x = sinf(player->angle + M_PI_2);
	player->plane.y = cosf(player->angle + M_PI_2);
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

void	move_player(t_data *data)
{
	if (data->key_tab[0] == 1)
		data->player->angle -= 0.03f;
	else if (data->key_tab[1] == 1)
		data->player->angle += 0.03f;
	if (data->key_tab[2] && data->key_tab[4])
		return (move(data, 0.042f, 0.0f), move(data, 0.042f, M_PI_2));
	if (data->key_tab[2] && data->key_tab[5])
		return (move(data, 0.042f, 0.0f), move(data, -0.042f, M_PI_2));
	if (data->key_tab[3] && data->key_tab[4])
		return (move(data, -0.042f, 0.0f), move(data, 0.042f, M_PI_2));
	if (data->key_tab[3] && data->key_tab[5])
		return (move(data, -0.042f, 0.0f), move(data, -0.042f, M_PI_2));
	if (data->key_tab[2] == 1)
		move(data, 0.1f, 0.0f);
	if (data->key_tab[3] == 1)
		move(data, -0.1f, 0.0f);
	if (data->key_tab[4] == 1)
		move(data, 0.1f, M_PI_2);
	if (data->key_tab[5] == 1)
		move(data, -0.1f, M_PI_2);
}
