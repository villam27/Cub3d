/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/25 19:33:34 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	**create_map()
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
			if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1 || (i == 6 && j < 12) || (i == 14 && j > 7))
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

long    get_frame_time(long    start_time)
{
    long            current_time;
    struct timeval    time;

    gettimeofday(&time, NULL);
    current_time = time.tv_usec - start_time;
    return (current_time);
}

long    get_start_time(void)
{
    struct timeval    time;
    long            start_time;

    gettimeofday(&time, NULL);
    start_time = time.tv_usec;
    return (start_time);
}

//static int	find_mask(int texture_h)
//{
//	int	i;
//	int	nb;
//
//	i = 0;
//	nb = texture_h;
//	while (nb)
//	{
//		nb = texture_h >> i;
//		i++;
//	}
//	return (1 << (i));
//}

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
			//data->ray.delta.x = sqrt(1 + (data->ray.dir.y * data->ray.dir.y) / (data->ray.dir.x * data->ray.dir.x));
		else
			data->ray.delta.x = FLT_MAX;
		if (data->ray.dir.y)
			data->ray.delta.y = fabsf(1.0f / data->ray.dir.y);
			//data->ray.delta.y = sqrt(1 + (data->ray.dir.x * data->ray.dir.x) / (data->ray.dir.y * data->ray.dir.y));
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
		wall_size = (int)((data->ilx->window->win_height * 0.9f / wall_dist));
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

int	ft_render_next_frame(t_data *data)
{
	static long	prev_time;
    static long	frame_time;
    int			fps;
    float		time;
	char		*fps_str;

    prev_time = get_start_time();

	move_player(data);
	update_player_plane(data->player);
	update_player_dir(data->player);
	draw_background(data->ilx->window, 0x87CEFA, 0x353535);
	if (!data->clic)
		ilx_change_button_color(data);
	update_ray(data);
	ilx_draw_gui(data->ilx, data->current_gui);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);
	frame_time = get_frame_time(prev_time);
    time = (float)frame_time / 1000000.0f;
    fps = 1 / time;
	fps_str = ft_itoa(fps);
	mlx_string_put(data->ilx->mlx, data->ilx->window->window, 5, 15, 0, fps_str);
	free(fps_str);
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
	int				**map;
	int				tmp;

	player.pos.x = 4.0f;
	player.pos.y = 5.0f;
	player.angle = M_PI_2;
	map = create_map();
	ilx = ilx_init();
	ilx.window = ilx_create_window(&ilx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	test = ilx_create_gui();

	data.clic = 0;
	mlx_mouse_get_pos(ilx.mlx, ilx.window->window, &data.prev_x, &tmp);
	data.enable_input = 1;
	data.map = map;
	data.player = &player;
	data.gui = test;
	data.current_gui = data.gui;
	data.ilx = &ilx;
	data.north_texture = ilx_create_texture(data.ilx, "assets/bluestone.xpm");
	data.south_texture = ilx_create_texture(data.ilx, "assets/eagle.xpm");
	data.west_texture = ilx_create_texture(data.ilx, "assets/redbrick.xpm");
	data.east_texture = ilx_create_texture(data.ilx, "assets/wood.xpm");
	data.key_tab = malloc(sizeof(uint8_t) * 6);
	ft_bzero(data.key_tab, sizeof(uint8_t) * 6);

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
	mlx_hook(ilx.window->window, ON_MOUSEMOVE, 1L << 6, rotate, &data);
	mlx_hook(ilx.window->window, ON_KEYUP, 1L << 1, ft_up_key, &data);
	mlx_hook(ilx.window->window, 8, 1L << 5, move_mouse, &data);
	mlx_loop(ilx.mlx);

	return (0);
}
