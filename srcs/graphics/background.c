/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:07:31 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/02 12:11:51 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_val(t_data *data, t_background *back)
{
	back->camera_z = 0.5f * data->ilx->window->win_height;
	back->floor = (uint32_t *)data->floor_texture->addr;
	back->ceiling = (uint32_t *)data->ceiling_texture->addr;
	back->ray_dir_1.x = data->player->dir.x + data->player->plane.x;
	back->ray_dir_1.y = data->player->dir.y + data->player->plane.y;
	back->ray_dir_2.x = data->player->dir.x - data->player->plane.x;
	back->ray_dir_2.y = data->player->dir.y - data->player->plane.y;
}

static void	find_pos(t_data *data, t_background *back, int y)
{
	back->horizon = y - (data->ilx->window->win_height >> 1);
	back->camera_dist = back->camera_z / back->horizon;
	back->step.x = back->camera_dist * (back->ray_dir_2.x - back->ray_dir_1.x)
		/ data->ilx->window->win_width;
	back->step.y = back->camera_dist * (back->ray_dir_2.y - back->ray_dir_1.y)
		/ data->ilx->window->win_width;
	back->floor_pos.x = data->player->pos.x + back->camera_dist
		* back->ray_dir_1.x;
	back->floor_pos.y = data->player->pos.y + back->camera_dist
		* back->ray_dir_1.y;
}

static void	get_pixel_color(t_data *data, t_background *back, int x, int y)
{
	back->cell.x = (int)(back->floor_pos.x);
	back->cell.y = (int)(back->floor_pos.y);
	back->f_texture_coord.x = (int)(data->floor_texture->w
			* (back->floor_pos.x - back->cell.x))
		& (data->floor_texture->w - 1);
	back->f_texture_coord.y = (int)(data->floor_texture->h
			* (back->floor_pos.y - back->cell.y))
		& (data->floor_texture->h - 1);
	back->floor_pos.x += back->step.x;
	back->floor_pos.y += back->step.y;
	data->ilx->window->renderer[x
		+ (data->ilx->window->win_height - y - 1)
		* data->ilx->window->win_width]
		= back->ceiling[back->f_texture_coord.x
		+ back->f_texture_coord.y * data->floor_texture->w];
	data->ilx->window->renderer[x + y * data->ilx->window->win_width]
		= back->floor[back->f_texture_coord.x + back->f_texture_coord.y
		* data->floor_texture->w];
}

void	draw_textured_background(t_data *data)
{
	int				x;
	int				y;
	t_background	back;

	y = 0;
	init_val(data, &back);
	while (y < data->ilx->window->win_height)
	{
		x = 0;
		find_pos(data, &back, y);
		while (x < data->ilx->window->win_width)
		{
			get_pixel_color(data, &back, x, y);
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
