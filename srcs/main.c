/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/11 14:05:39 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_data *data)
{
	ilx_draw_fill_rect(data->ilx->window, &data->minimap.background, 0);
}

//draw_background(data->ilx->window, 0x87CEFA, 0x353535);
int	ft_render_next_frame(t_data *data)
{
	static long		prev_time;
	static long		frame_time;
	static double	time = 0;
	static int		i = 0;

	prev_time = get_start_time();
	move_player(data, time);
	update_player_plane(data->player);
	update_player_dir(data->player);
	draw_textured_background(data);
	if (!data->clic)
		ilx_change_button_color(data);
	update_ray(data);
	ilx_draw_gui(data->ilx, data->current_gui);
	draw_minimap(data);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);
	frame_time = get_frame_time(prev_time);
	time = frame_time / 1000.0;
	i++;
	return (0);
}

void	print_map(int **map, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j] == BT_FILL)
				printf("\033[31m%d \033[0m", map[i][j]);
			else if (map[i][j] == WALL)
				printf("\033[33m%d \033[0m", map[i][j]);
			else
				printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

t_ilx	*init_ilx_data(void)
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
	data->player = NULL;
	data->key_tab = NULL;
	data->west_texture = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->floor_texture = NULL;
	data->ceiling_texture = NULL;
	data->z_buffer = NULL;
	return (data);
}

void	destroy_everything(t_data *data)
{
	ilx_destroy_texture(data->ilx, data->west_texture);
	ilx_destroy_texture(data->ilx, data->north_texture);
	ilx_destroy_texture(data->ilx, data->south_texture);
	ilx_destroy_texture(data->ilx, data->east_texture);
	ilx_destroy_texture(data->ilx, data->floor_texture);
	ilx_destroy_texture(data->ilx, data->ceiling_texture);
	ilx_destroy_gui(data->gui);
	free(data->map);
	free(data->player);
	free(data->key_tab);
	free(data->z_buffer);
	free(data->ilx);
	free(data);
}

/*
	TODO: Exit if not valid map
*/
int	main(void)
{
	t_ilx			ilx;
	t_data			*data;
	t_gui			*test;
	t_button		*quit_b;
	t_player		player;
	int				tmp;

	//player init
	player.pos.x = 2.0f;
	player.pos.y = 2.0f;
	player.angle = M_PI_2;
	player.normal_speed = 4.0f;
	player.player_speed = player.normal_speed;
	player.rotation_speed = M_PI;
	player.sprint_speed = 8.0f;
	player.sneak_speed = 2.0f;
	
	//ilx init
	ilx = ilx_init();
	ilx.window = ilx_create_window(&ilx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	test = ilx_create_gui();

	data = create_data();
	data->clic = 0;
	mlx_mouse_get_pos(ilx.mlx, ilx.window->window, &data->prev_x, &tmp);
	data->enable_input = 1;
	data->player = &player;
	data->gui = test;
	data->current_gui = data->gui;
	data->ilx = &ilx;
	data->west_texture = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->floor_texture = NULL;
	data->ceiling_texture = NULL;
	if (!load_maps(data, "maps/map01.cub"))
		ft_printf("Error not a valid map exit\n");
	data->key_tab = malloc(sizeof(uint8_t) * 6);
	ft_bzero(data->key_tab, sizeof(uint8_t) * 6);
	data->z_buffer = malloc(sizeof(float) * data->ilx->window->win_width);
	data->minimap.background = ilx_new_rect(20.0f, 20.0f, 200.0f, 200.0f);

	quit_b = ilx_create_button(350, 500, 90, 40);
	ilx_background_button_color(quit_b, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(quit_b, 0xffffff, 0, 0);
	ilx_add_button_label(quit_b, "Quit");

	ilx_add_button(test, quit_b, &quit);

	//print_map(data.map);
	mlx_loop_hook(ilx.mlx, ft_render_next_frame, data);
	mlx_hook(ilx.window->window, ON_DESTROY, 0, cross_quit, data);
	mlx_hook(ilx.window->window, ON_MOUSEDOWN, 1L << 2, on_clic, data);
	mlx_hook(ilx.window->window, ON_MOUSEUP, 1L << 3, on_release, data);
	mlx_hook(ilx.window->window, ON_KEYDOWN, 1L << 0, ft_press_key, data);
	mlx_hook(ilx.window->window, ON_KEYUP, 1L << 1, ft_up_key, data);
	mlx_hook(ilx.window->window, ON_MOUSEMOVE, 1L << 6, rotate, data);
	mlx_hook(ilx.window->window, EXIT_WIN, 1L << 5, move_mouse, data);
	mlx_loop(ilx.mlx);

	return (0);
}
