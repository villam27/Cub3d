/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:07:31 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 13:13:22 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_textured_background(t_data *data)
{
	t_vec2d		ray_dir_1;
	t_vec2d		ray_dir_2;
	t_vec2d		step;
	t_vec2d		floor_pos;
	t_ivec2d	cell;
	t_ivec2d	f_texture_coord;
	t_ivec2d	c_texture_coord;
	int			horizon;
	float		camera_z;
	float		camera_dist;
	int			y;
	int			x;
	uint32_t	*floor;
	uint32_t	*ceiling;

	y = 0;
	camera_z = 0.5f * data->ilx->window->win_height;
	floor = (uint32_t *)data->floor_texture->addr;
	ceiling = (uint32_t *)data->ceiling_texture->addr;
	while (y < data->ilx->window->win_height)
	{
		x = 0;
		ray_dir_1.x = data->player->dir.x + data->player->plane.x;
		ray_dir_1.y = data->player->dir.y + data->player->plane.y;
		ray_dir_2.x = data->player->dir.x - data->player->plane.x;
		ray_dir_2.y = data->player->dir.y - data->player->plane.y;
		horizon = y - (data->ilx->window->win_height >> 1);
		camera_dist = camera_z / horizon;
		step.x = camera_dist * (ray_dir_2.x - ray_dir_1.x) / data->ilx->window->win_width;
		step.y = camera_dist * (ray_dir_2.y - ray_dir_1.y) / data->ilx->window->win_width;
		floor_pos.x = data->player->pos.x + camera_dist * ray_dir_1.x;
		floor_pos.y = data->player->pos.y + camera_dist * ray_dir_1.y;
		while (x < data->ilx->window->win_width)
		{
			cell.x = (int)(floor_pos.x);
			cell.y = (int)(floor_pos.y);
			f_texture_coord.x = (int)(data->floor_texture->w * (floor_pos.x - cell.x)) & (data->floor_texture->w - 1);
			f_texture_coord.y = (int)(data->floor_texture->h * (floor_pos.y - cell.y)) & (data->floor_texture->h - 1);
			c_texture_coord.x = (int)(data->ceiling_texture->w * (floor_pos.x - cell.x)) & (data->ceiling_texture->w - 1);
			c_texture_coord.y = (int)(data->ceiling_texture->h * (floor_pos.y - cell.y)) & (data->ceiling_texture->h - 1);
			floor_pos.x += step.x;
			floor_pos.y += step.y;
			data->ilx->window->renderer[x + (data->ilx->window->win_height - y - 1) * data->ilx->window->win_width] = ceiling[c_texture_coord.x + c_texture_coord.y * data->ceiling_texture->w];
			data->ilx->window->renderer[x + y * data->ilx->window->win_width] = floor[f_texture_coord.x + f_texture_coord.y * data->floor_texture->w];
			x++;
		}
		y++;
	}
}

void	draw_background(t_window *window, uint32_t color_ceiling,
			uint32_t color_floor)
{
	int	i;
	int	max;
	int	max2;

	max2 = window->win_height * window->win_width;
	max = max2 >> 1;
	i = 0;
	while (i < max)
	{
		window->renderer[i] = color_ceiling;
		i++;
	}
	while (i < max2)
	{
		window->renderer[i] = color_floor;
		i++;
	}
}
