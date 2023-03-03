/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/03 10:42:26 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	**create_map(void)
{
	int	**map;
	int	i;
	int	j;

	i = 0;
	map = malloc(sizeof(int *) * MAP_HEIGHT);
	while (i < MAP_HEIGHT)
	{
		j = 0;
		map[i] = malloc(sizeof(int) * MAP_WIDTH);
		while (j < MAP_WIDTH)
		{
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1
				|| (i == 6 && j < 12) || (i == 14 && j > 7))
				map[i][j] = 1;
			else
				map[i][j] = 0;
			j++;
		}
		i++;
	}
	map[7][11] = 1;
	map[8][11] = 1;
	map[9][11] = 1;
	map[2][1] = 1;
	map[2][2] = 1;
	map[2][3] = 1;
	map[2][4] = 1;
	map[2][5] = 1;
	map[10][4] = 1;
	return (map);
}

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
	ilx_render_copy(data->ilx->window, data->test_texutre,
		&data->test_pts, &data->test_rect);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);
	if ((i % 10) == 0)
		data->test_rect.x += 28;
	if (data->test_rect.x > 28 * 5)
		data->test_rect.x = 0;
	frame_time = get_frame_time(prev_time);
	time = frame_time / 1000.0;
	i++;
	return (0);
}

void	print_map(int **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(void)
{
	t_ilx			ilx;
	t_data			data;
	t_gui			*test;
	t_button		*quit_b;
	t_player		player;
	int				tmp;

	player.pos.x = 4.0f;
	player.pos.y = 5.0f;
	player.angle = M_PI_2;
	player.normal_speed = 4.0f;
	player.player_speed = player.normal_speed;
	player.rotation_speed = M_PI;
	player.sprint_speed = 8.0f;
	player.sneak_speed = 2.0f;
	data.map = create_map();
	ilx = ilx_init();
	ilx.window = ilx_create_window(&ilx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	test = ilx_create_gui();

	data.clic = 0;
	mlx_mouse_get_pos(ilx.mlx, ilx.window->window, &data.prev_x, &tmp);
	data.enable_input = 1;
	data.player = &player;
	data.gui = test;
	data.current_gui = data.gui;
	data.ilx = &ilx;
	data.north_texture = ilx_create_texture(data.ilx, "assets/bluestone.xpm");
	data.south_texture = ilx_create_texture(data.ilx, "assets/eagle.xpm");
	data.west_texture = ilx_create_texture(data.ilx, "assets/redbrick.xpm");
	data.east_texture = ilx_create_texture(data.ilx, "assets/purplestone.xpm");
	data.floor_texture = ilx_create_texture(data.ilx, "assets/colorstone.xpm");
	data.ceiling_texture = ilx_create_texture(data.ilx, "assets/wood.xpm");
	data.test_texutre = ilx_create_texture(data.ilx, "assets/lifes.xpm");
	data.test_pts = ilx_new_point(50, 50);
	data.test_rect = ilx_new_rect(0, 0, 28, 28);
	data.key_tab = malloc(sizeof(uint8_t) * 6);
	ft_bzero(data.key_tab, sizeof(uint8_t) * 6);
	data.z_buffer = malloc(sizeof(float) * data.ilx->window->win_width);
	data.minimap.background = ilx_new_rect(20.0f, 20.0f, 200.0f, 200.0f);

	quit_b = ilx_create_button(350, 500, 90, 40);
	ilx_background_button_color(quit_b, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(quit_b, 0xffffff, 0, 0);
	ilx_add_button_label(quit_b, "Quit");

	ilx_add_button(test, quit_b, &quit);

	print_map(data.map);
	mlx_loop_hook(ilx.mlx, ft_render_next_frame, &data);
	mlx_hook(ilx.window->window, ON_DESTROY, 0, cross_quit, &data);
	mlx_hook(ilx.window->window, ON_MOUSEDOWN, 1L << 2, on_clic, &data);
	mlx_hook(ilx.window->window, ON_MOUSEUP, 1L << 3, on_release, &data);
	mlx_hook(ilx.window->window, ON_KEYDOWN, 1L << 0, ft_press_key, &data);
	mlx_hook(ilx.window->window, ON_KEYUP, 1L << 1, ft_up_key, &data);
	mlx_hook(ilx.window->window, ON_MOUSEMOVE, 1L << 6, rotate, &data);
	mlx_hook(ilx.window->window, EXIT_WIN, 1L << 5, move_mouse, &data);
	mlx_loop(ilx.mlx);

	return (0);
}
