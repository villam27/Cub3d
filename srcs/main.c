/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/16 13:26:59 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_gun(t_data *data)
{
	static int	i = 0;
	static int	trig = 0;

	if (data->clic == -1)
		trig = 1;
	if (trig)
	{
		if (i % 7 == 0)
			data->gun_rect.x += 360;
		if (data->gun_rect.x > 1440 && i % 7 == 0)
		{
			data->gun_rect.x = 0;
			trig = 0;
		}
	}
	i++;
}

int	ft_render_next_frame(t_data *data)
{
	static long		prev_time;
	static long		frame_time;
	static double	time = 0;

	prev_time = get_start_time();
	move_player(data, time);
	update_player_plane(data->player);
	update_player_dir(data->player);
	if (data->ceiling_texture && data->floor_texture)
		draw_textured_background(data);
	else
		draw_background(data->ilx->window,
			data->ceiling_color, data->floor_color);
	if (!data->clic)
		ilx_change_button_color(data);
	update_ray(data);
	ilx_draw_gui(data->ilx, data->current_gui);
	ilx_render_copy(data->ilx->window, data->gun_texture,
		&data->gun_pos, &data->gun_rect);
	update_gun(data);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);
	frame_time = get_frame_time(prev_time);
	time = frame_time / 1000.0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ilx_err("Usage ./cub3d <path_to_map.cub>"), ERROR);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5))
		return (ilx_err("Not a .cub file"), ERROR);
	data = create_data();
	if (!data)
		return (ilx_err("initialization failed"), ERROR);
	if (init_all(data, argv[1]) == ERROR)
		return (ilx_err("initialization failed"), ERROR);
	mlx_loop_hook(data->ilx->mlx, ft_render_next_frame, data);
	mlx_hook(data->ilx->window->window, ON_DESTROY, 0, cross_quit, data);
	mlx_hook(data->ilx->window->window, ON_MOUSEDOWN, 1L << 2, on_clic, data);
	mlx_hook(data->ilx->window->window, ON_MOUSEUP, 1L << 3, on_release, data);
	mlx_hook(data->ilx->window->window, ON_KEYDOWN,
		1L << 0, ft_press_key, data);
	mlx_hook(data->ilx->window->window, ON_KEYUP, 1L << 1, ft_up_key, data);
	mlx_hook(data->ilx->window->window, ON_MOUSEMOVE, 1L << 6, rotate, data);
	mlx_hook(data->ilx->window->window, EXIT_WIN, 1L << 5, move_mouse, data);
	mlx_loop(data->ilx->mlx);
	return (SUCCESS);
}
