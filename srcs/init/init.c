/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:09:20 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/16 09:25:57 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_ilx	*init_ilx_data(void)
{
	t_ilx	*ilx;

	ilx = malloc(sizeof(t_ilx));
	if (!ilx)
		return (NULL);
	ilx->mlx = mlx_init();
	if (!ilx->mlx)
		return (free(ilx), NULL);
	ilx->window = NULL;
	return (ilx);
}

t_data	*create_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->ilx = NULL;
	data->gui = NULL;
	data->current_gui = NULL;
	data->map = NULL;
	data->map_data = NULL;
	data->player = NULL;
	data->key_tab = NULL;
	data->west_texture = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->floor_texture = NULL;
	data->ceiling_texture = NULL;
	data->gun_texture = NULL;
	data->gun_pos = ilx_new_point(WIN_WIDTH / 2, WIN_HEIGHT - 360);
	data->gun_rect = ilx_new_rect(0, 0, 360, 360);
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->z_buffer = NULL;
	return (data);
}

static t_player	*init_player(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	(void)data;
	player->pos.x = (float)data->map_data->player_pos.x + PLAYER_SPAWN_OFFSET;
	player->pos.y = (float)data->map_data->player_pos.y + PLAYER_SPAWN_OFFSET;
	if (data->map_data->direction == 'N')
		player->angle = M_PI;
	if (data->map_data->direction == 'W')
		player->angle = 3 * M_PI_2;
	if (data->map_data->direction == 'E')
		player->angle = M_PI_2;
	if (data->map_data->direction == 'S')
		player->angle = 0;
	player->normal_speed = NORMAL_SPEED;
	player->player_speed = player->normal_speed;
	player->rotation_speed = M_PI;
	player->sprint_speed = SPRINT_SPEED;
	player->sneak_speed = SNEAK_SPEED;
	return (player);
}

static int	create_buttons(t_data *data)
{
	t_button		*quit_b;
	t_button		*start_b;

	quit_b = ilx_create_button(50, 400, 150, 60);
	if (!quit_b)
		return (ERROR);
	ilx_background_button_color(quit_b, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(quit_b, 0xffffff, 0, 0);
	ilx_add_button_label(quit_b, "Quit Game");
	ilx_add_button(data->gui, quit_b, &quit);
	start_b = ilx_create_button(50, 300, 150, 60);
	if (!start_b)
		return (ERROR);
	ilx_background_button_color(start_b, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(start_b, 0xffffff, 0, 0);
	ilx_add_button_label(start_b, "Start Game");
	ilx_add_button(data->gui, start_b, &start);
	return (SUCCESS);
}

int	init_all(t_data *data, char *map_path)
{
	data->ilx = init_ilx_data();
	if (!data->ilx)
		return (destroy_everything(data), ERROR);
	data->ilx->window = ilx_create_window(data->ilx,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	data->gui = ilx_create_gui();
	if (!data->gui || !data->ilx->window)
		return (destroy_everything(data), ERROR);
	if (load_maps(data, map_path) == ERROR || create_buttons(data) == ERROR)
		return (destroy_everything(data), ERROR);
	data->current_gui = data->gui;
	data->clic = 0;
	data->enable_input = 1;
	data->player = init_player(data);
	data->key_tab = malloc(sizeof(uint8_t) * 6);
	data->gun_texture = ilx_create_texture(data->ilx, "assets/gun.xpm");
	if (!data->key_tab || !data->player || !data->gun_texture)
		return (destroy_everything(data), ERROR);
	ft_bzero(data->key_tab, sizeof(uint8_t) * 6);
	data->z_buffer = malloc(sizeof(float) * data->ilx->window->win_width);
	if (!data->z_buffer)
		return (destroy_everything(data), ERROR);
	return (SUCCESS);
}
