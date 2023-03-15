/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/15 21:21:40 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_data *data)
{
	ilx_draw_fill_rect(data->ilx->window, &data->minimap.background, 0);
}

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
	if (data->ceiling_texture && data->floor_texture)
		draw_textured_background(data);
	else
		draw_background(data->ilx->window,
			data->ceiling_color, data->floor_color);
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

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_printf("Error: usage %s <path_to_map>\n", argv[0]), ERROR);
	data = create_data();
	if (init_all(data, argv[1]) == ERROR)
		return (ft_printf("Error on init\n"), ERROR);
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
