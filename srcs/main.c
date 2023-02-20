/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/20 22:20:30 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"
#include "utils.h"
#include "gui.h"
#include "ilx_texture.h"
#include <math.h>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

typedef struct s_vec2d
{
	float	x;
	float	y;
}	t_vec2d;

typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	float	angle;
}	t_player;

typedef struct s_data
{
	t_ilx		*ilx;
	t_gui		*gui;
	uint8_t		clic;
	uint8_t		enable_input;
	t_gui		*current_gui;
	int			**map;
	t_player	*player;
	uint8_t		*key_tab;
}	t_data;

t_rectangle	player_tile;

void	update_player_dir(t_player *player)
{
	player->dir.x = sinf(player->angle);
	player->dir.y = cosf(player->angle);
}

void	ilx_change_button_color(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	if (!data->current_gui)
		return ;
	mlx_mouse_get_pos(data->ilx->mlx, data->ilx->window->window, &x, &y);
	while (data->current_gui->buttons[i].label)
	{
		if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].under_cursor_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].under_cursor_label;
			return ;
		}
		else if (data->current_gui->buttons[i].current_color
			== data->current_gui->buttons[i].under_cursor_background)
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].default_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].default_label;
		}
		i++;
	}
}

int	on_clic(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == RIGHT_CLICK)
	{
		if (!data->current_gui)
			data->current_gui = data->gui;
		else
			data->current_gui = NULL;
	}
	if (key == LEFT_CLICK && data->current_gui)
	{
		data->clic = 1;
		while (data->current_gui->buttons[i].label)
		{
			if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			{
				data->current_gui->buttons[i].current_color
					= data->current_gui->buttons[i].clicked_background;
				data->current_gui->buttons[i].current_label_color
					= data->current_gui->buttons[i].clicked_label;
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	on_release(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == LEFT_CLICK && data->current_gui)
	{
		data->clic = 0;
		while (data->current_gui->buttons[i].label)
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].default_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].default_label;
			i++;
		}
		i = 0;
		while (data->current_gui->buttons[i].label)
		{
			if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			{
				(*data->current_gui->buttons[i].f)(data);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

void	ilx_destroy_window(t_ilx *ilx)
{
	mlx_destroy_image(ilx->mlx, ilx->window->img);
	mlx_destroy_window(ilx->mlx, ilx->window->window);
	free(ilx->window->win_name);
	free(ilx->window);
}

void	*quit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ilx_destroy_window(data->ilx);
	mlx_destroy_display(data->ilx->mlx);
	ilx_destroy_gui(data->gui);
	free(data->ilx->mlx);
	exit (0);
}

int	cross_quit(void *param)
{
	quit(param);
	return (0);
}

void	move(t_data *data, float value, float angle_offset)
{
	float	x_step;
	float	y_step;
	
	x_step = data->player->pos.x + sinf(data->player->angle + angle_offset) * value;
	y_step = data->player->pos.y + cosf(data->player->angle + angle_offset) * value;
	if (!data->map[(int)y_step / 30][(int)data->player->pos.x / 30])
		data->player->pos.y = y_step;
	if (!data->map[(int)data->player->pos.y / 30][(int)x_step / 30])
		data->player->pos.x = x_step;
}

int	ft_press_key(int keycode, t_data *data)
{
	if (keycode == RIGHT)
		data->key_tab[0] = 1;
	else if (keycode == LEFT)
		data->key_tab[1] = 1;
	else if (keycode == W)
		data->key_tab[2] = 1;
	else if (keycode == S)
		data->key_tab[3] = 1;
	else if (keycode == A)
		data->key_tab[4] = 1;
	else if (keycode == D)
		data->key_tab[5] = 1;
	return (0);
}

int	ft_up_key(int keycode, t_data *data)
{
	if (keycode == RIGHT)
		data->key_tab[0] = 0;
	else if (keycode == LEFT)
		data->key_tab[1] = 0;
	else if (keycode == W)
		data->key_tab[2] = 0;
	else if (keycode == S)
		data->key_tab[3] = 0;
	else if (keycode == A)
		data->key_tab[4] = 0;
	else if (keycode == D)
		data->key_tab[5] = 0;
	return (0);
}

void	draw_map(int **map, t_ilx *ilx)
{
	int			i;
	int			j;
	t_rectangle	tile;

	i = 0;
	tile.width = 30;
	tile.height = 30;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		tile.y = 30 * i;
		while (j < MAP_WIDTH)
		{
			tile.x = 30 * j;
			if (map[i][j])
				ilx_draw_fill_rect(ilx->window, &tile, 0xff);
			else
				ilx_draw_fill_rect(ilx->window, &tile, 0xff00);
			j++;
		}
		i++;
	}
}

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
	return (map);
}

void	draw_player(t_ilx *ilx, t_player *player)
{
	t_line	direction;

	direction = ilx_set_line(player->pos.x , player->pos.y, player->pos.x + 20.0f * player->dir.x, player->pos.y + 20.0f * player->dir.y);
	ilx_draw_line(ilx->window, &direction, 1, 0xff0000);
	player_tile.height = 10;
	player_tile.width = 10;
	player_tile.x = player->pos.x - 5.0f;
	player_tile.y = player->pos.y - 5.0f;
	ilx_draw_fill_rect(ilx->window, &player_tile, 0xff0000);
}

void	move_player(t_data *data)
{
	if (data->key_tab[0] == 1)
		data->player->angle -= 0.01f;
	else if (data->key_tab[1] == 1)
		data->player->angle += 0.01f;
	if (data->key_tab[2] && data->key_tab[4])
	{
		move(data, 0.6f, 0.0f);
		move(data, 0.6f, M_PI_2);
		return ;
	}
	if (data->key_tab[2] && data->key_tab[5])
	{
		move(data, 0.6f, 0.0f);
		move(data, -0.6f, M_PI_2);
		return ;
	}
	if (data->key_tab[3] && data->key_tab[4])
	{
		move(data, -0.6f, 0.0f);
		move(data, 0.6f, M_PI_2);
		return ;
	}
	if (data->key_tab[3] && data->key_tab[5])
	{
		move(data, -0.6f, 0.0f);
		move(data, -0.6f, M_PI_2);
		return ;
	}
	if (data->key_tab[2] == 1)
		move(data, 1.0f, 0.0f);
	if (data->key_tab[3] == 1)
		move(data, -1.0f, 0.0f);
	if (data->key_tab[4] == 1)
		move(data, 1.0f, M_PI_2);
	if (data->key_tab[5] == 1)
		move(data, -1.0f, M_PI_2);
}

void	print_input(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		printf("%d ", data->key_tab[i]);
	printf("\n");
}

int	ft_render_next_frame(t_data *data)
{
	move_player(data);
	update_player_dir(data->player);
	ilx_clear_window(data->ilx->window, 0);
	if (!data->clic)
		ilx_change_button_color(data);
	draw_map(data->map, data->ilx);
	draw_player(data->ilx, data->player);
	ilx_draw_gui(data->ilx, data->current_gui);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);
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
	int				**map; 
	t_player		player;

	player.pos.x = 150.0f;
	player.pos.y = 150.0f;
	player.angle = M_PI;
	map = create_map();
	ilx = ilx_init(); 
	ilx.window = ilx_create_window(&ilx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	test = ilx_create_gui();

	data.clic = 0;
	data.enable_input = 1;
	data.current_gui = NULL;
	data.map = map;
	data.player = &player;
	data.key_tab = malloc(sizeof(uint8_t) * 6);
	ft_bzero(data.key_tab, sizeof(uint8_t) * 6);

	quit_b = ilx_create_button(350, 500, 90, 40);
	ilx_background_button_color(quit_b, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(quit_b, 0xffffff, 0, 0);
	ilx_add_button_label(quit_b, "Quit");

	ilx_add_button(test, quit_b, &quit);

	data.ilx = &ilx;
	data.gui = test;
	print_map(data.map);
	mlx_loop_hook(ilx.mlx, ft_render_next_frame, &data);
	mlx_hook(ilx.window->window, ON_DESTROY, 0, cross_quit, &data);
	mlx_hook(ilx.window->window, ON_MOUSEDOWN, 1L << 2, on_clic, &data);
	mlx_hook(ilx.window->window, ON_MOUSEUP, 1L << 3, on_release, &data);
	mlx_hook(ilx.window->window, ON_KEYDOWN, 1L << 0, ft_press_key, &data);
	mlx_hook(ilx.window->window, ON_KEYUP, 1L << 1, ft_up_key, &data);
	mlx_loop(ilx.mlx);

	return (0);
}
