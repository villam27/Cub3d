/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:54:02 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 13:16:06 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_ray(t_data *data)
{
	int				i;
	int				hit;
	int				side;
	float			x_view;
	float			wall_dist;
	float			wall_x;
	int				start;
	int				end;
	int				wall_size;
	t_ilx_texture	*current_texture;
	int				texture_x;
	int				texture_y;
	float			texture_step;
	float			texture_pos;
	int				mask;

	i = 0;
	while (i < data->ilx->window->win_width)
	{
		hit = 0;
		x_view = (i << 1) / (float)data->ilx->window->win_width - 1;
		data->ray.dir.x = data->player->dir.x + data->player->plane.x * x_view;
		data->ray.dir.y = data->player->dir.y + data->player->plane.y * x_view;
		data->ray.pos.x = (int)data->player->pos.x;
		data->ray.pos.y = (int)data->player->pos.y;
		if (data->ray.dir.x)
			data->ray.delta.x = fabsf(1.0f / data->ray.dir.x);
		else
			data->ray.delta.x = FLT_MAX;
		if (data->ray.dir.y)
			data->ray.delta.y = fabsf(1.0f / data->ray.dir.y);
		else
			data->ray.delta.y = FLT_MAX;
		if (data->ray.dir.x < 0)
		{
			data->ray.step.x = -1.0f;
			data->ray.dist.x = (data->player->pos.x - data->ray.pos.x) * data->ray.delta.x;
		}
		else
		{
			data->ray.step.x = 1.0f;
			data->ray.dist.x = (data->ray.pos.x + 1.0f - data->player->pos.x) * data->ray.delta.x;
		}
		if (data->ray.dir.y < 0)
		{
			data->ray.step.y = -1.0f;
			data->ray.dist.y = (data->player->pos.y - data->ray.pos.y) * data->ray.delta.y;
		}
		else
		{
			data->ray.step.y = 1.0f;
			data->ray.dist.y = (data->ray.pos.y + 1.0f - data->player->pos.y) * data->ray.delta.y;
		}
		while (!hit)
		{
			if (data->ray.dist.x < data->ray.dist.y)
			{
				data->ray.dist.x += data->ray.delta.x;
				data->ray.pos.x += data->ray.step.x;
				if (data->ray.dir.x > 0)
					side = 0;
				else
					side = 1;
			}
			else
			{
				data->ray.dist.y += data->ray.delta.y;
				data->ray.pos.y += data->ray.step.y;
				if (data->ray.dir.y > 0)
					side = 2;
				else
					side = 3;
			}
			if (data->map[(int)data->ray.pos.y][(int)data->ray.pos.x])
				hit = 1;
		}
		if (side == 0 || side == 1)
		{
			wall_dist = (data->ray.dist.x - data->ray.delta.x);
			wall_x = data->player->pos.y + wall_dist * data->ray.dir.y;
		}
		else
		{
			wall_dist = (data->ray.dist.y - data->ray.delta.y);
			wall_x = data->player->pos.x + wall_dist * data->ray.dir.x;
		}
		wall_x -= (float)floor((double)wall_x);
		wall_size = (int)((data->ilx->window->win_height / wall_dist));
		start = (-wall_size >> 1) + (data->ilx->window->win_height >> 1);
		if (start < 0)
			start = 0;
		end = (wall_size >> 1) + (data->ilx->window->win_height >> 1);
		if (end > data->ilx->window->win_height)
			end = data->ilx->window->win_height;
		if (side == 1)
		{
			current_texture = data->west_texture;
			texture_x = (int)(wall_x * (float)data->west_texture->w);
			texture_x = data->west_texture->w - texture_x - 1;
		}
		else if (side == 2)
		{
			current_texture = data->south_texture;
			texture_x = (int)(wall_x * (float)data->south_texture->w);
			texture_x = data->south_texture->w - texture_x - 1;
		}
		else if (side == 3)
		{
			current_texture = data->north_texture;
			texture_x = (int)(wall_x * (float)data->north_texture->w);
		}
		else
		{
			current_texture = data->east_texture;
			texture_x = (int)(wall_x * (float)data->east_texture->w);
		}
		texture_step = current_texture->h / (float)wall_size;
		texture_pos = (start - (data->ilx->window->win_height >> 1) + (wall_size >> 1)) * texture_step;
		mask = current_texture->h -1;
		int	x = data->ilx->window->win_width - i - 1;
		start *= data->ilx->window->win_width;
		end *= data->ilx->window->win_width;
		while (start < end)
		{
			texture_y = (int)texture_pos & mask;
			texture_pos += texture_step;
			data->ilx->window->renderer[x + start] = current_texture->buffer[current_texture->w * texture_y + texture_x];
			start += data->ilx->window->win_width;
		}
		i++;
	}
}
