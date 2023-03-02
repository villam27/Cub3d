/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:54:02 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/02 11:35:33 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	shooting_ray(t_data *data, t_raycast *raycast)
{
	while (!raycast->hit)
	{
		if (data->ray.dist.x < data->ray.dist.y)
		{
			data->ray.dist.x += data->ray.delta.x;
			data->ray.pos.x += data->ray.step.x;
			if (data->ray.dir.x > 0)
				raycast->side = 0;
			else
				raycast->side = 1;
		}
		else
		{
			data->ray.dist.y += data->ray.delta.y;
			data->ray.pos.y += data->ray.step.y;
			if (data->ray.dir.y > 0)
				raycast->side = 2;
			else
				raycast->side = 3;
		}
		if (data->map[(int)data->ray.pos.y][(int)data->ray.pos.x])
			raycast->hit = 1;
	}
}

static void	get_wall_size(t_data *data, t_raycast *raycast)
{
	if (raycast->side == 0 || raycast->side == 1)
	{
		raycast->wall_dist = (data->ray.dist.x - data->ray.delta.x);
		raycast->wall_x = data->player->pos.y + raycast->wall_dist
			* data->ray.dir.y;
	}
	else
	{
		raycast->wall_dist = (data->ray.dist.y - data->ray.delta.y);
		raycast->wall_x = data->player->pos.x + raycast->wall_dist
			* data->ray.dir.x;
	}
	raycast->wall_x -= (float)floor((double)raycast->wall_x);
	raycast->wall_size = (int)((data->ilx->window->win_height
				/ raycast->wall_dist));
	raycast->start = (-raycast->wall_size >> 1)
		+ (data->ilx->window->win_height >> 1);
	if (raycast->start < 0)
		raycast->start = 0;
	raycast->end = (raycast->wall_size >> 1)
		+ (data->ilx->window->win_height >> 1);
	if (raycast->end > data->ilx->window->win_height)
		raycast->end = data->ilx->window->win_height;
}

static void	get_wall_texture(t_data *data, t_raycast *raycast)
{
	if (raycast->side == 1)
	{
		raycast->current_texture = data->west_texture;
		raycast->texture_x = (int)(raycast->wall_x * data->west_texture->w);
		raycast->texture_x = data->west_texture->w - raycast->texture_x - 1;
	}
	else if (raycast->side == 2)
	{
		raycast->current_texture = data->south_texture;
		raycast->texture_x = (int)(raycast->wall_x * data->south_texture->w);
		raycast->texture_x = data->south_texture->w - raycast->texture_x - 1;
	}
	else if (raycast->side == 3)
	{
		raycast->current_texture = data->north_texture;
		raycast->texture_x = (int)(raycast->wall_x * data->north_texture->w);
	}
	else
	{
		raycast->current_texture = data->east_texture;
		raycast->texture_x = (int)(raycast->wall_x * data->east_texture->w);
	}
}

static void	draw_wall(t_data *data, t_raycast *raycast, int x)
{
	while (raycast->start < raycast->end)
	{
		raycast->texture_y = (int)raycast->texture_pos & raycast->mask;
		raycast->texture_pos += raycast->texture_step;
		data->ilx->window->renderer[x + raycast->start]
			= raycast->current_texture->buffer[raycast->current_texture->w
			* raycast->texture_y + raycast->texture_x];
		raycast->start += data->ilx->window->win_width;
	}
}

void	update_ray(t_data *data)
{
	t_raycast	raycast;
	int			i;
	int			x;

	i = 0;
	while (i < data->ilx->window->win_width)
	{
		init_ray_val(data, &raycast, i);
		init_step_ray(data);
		shooting_ray(data, &raycast);
		get_wall_size(data, &raycast);
		get_wall_texture(data, &raycast);
		raycast.texture_step = raycast.current_texture->h
			/ (float)raycast.wall_size;
		raycast.texture_pos = (raycast.start
				- (data->ilx->window->win_height >> 1)
				+ (raycast.wall_size >> 1)) * raycast.texture_step;
		raycast.mask = raycast.current_texture->h -1;
		x = data->ilx->window->win_width - i - 1;
		raycast.start *= data->ilx->window->win_width;
		raycast.end *= data->ilx->window->win_width;
		draw_wall(data, &raycast, x);
		i++;
	}
}
