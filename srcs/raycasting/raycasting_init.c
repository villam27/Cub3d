/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:35:21 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/02 11:35:39 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray_val(t_data *data, t_raycast *raycast, int i)
{
	raycast->hit = 0;
	raycast->x_view = (i << 1) / (float)data->ilx->window->win_width - 1;
	data->ray.dir.x = data->player->dir.x + data->player->plane.x
		* raycast->x_view;
	data->ray.dir.y = data->player->dir.y + data->player->plane.y
		* raycast->x_view;
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
}

void	init_step_ray(t_data *data)
{
	if (data->ray.dir.x < 0)
	{
		data->ray.step.x = -1.0f;
		data->ray.dist.x = (data->player->pos.x - data->ray.pos.x)
			* data->ray.delta.x;
	}
	else
	{
		data->ray.step.x = 1.0f;
		data->ray.dist.x = (data->ray.pos.x + 1.0f - data->player->pos.x)
			* data->ray.delta.x;
	}
	if (data->ray.dir.y < 0)
	{
		data->ray.step.y = -1.0f;
		data->ray.dist.y = (data->player->pos.y - data->ray.pos.y)
			* data->ray.delta.y;
	}
	else
	{
		data->ray.step.y = 1.0f;
		data->ray.dist.y = (data->ray.pos.y + 1.0f - data->player->pos.y)
			* data->ray.delta.y;
	}
}
