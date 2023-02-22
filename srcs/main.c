/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/22 15:56:26 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"
#include "utils.h"
#include "gui.h"
#include "ilx_texture.h"
#include <math.h>
#include <float.h>

#include <sys/time.h>

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
	t_vec2d	plane;
	float	angle;
}	t_player;

typedef struct s_ray
{
	t_vec2d dir;
	t_vec2d	delta;
	t_vec2d	dist;
	t_vec2d	step;
	t_vec2d	pos;
}	t_ray;

typedef struct s_data
{
	t_ilx			*ilx;
	t_gui			*gui;
	uint8_t			clic;
	uint8_t			enable_input;
	t_gui			*current_gui;
	int				**map;
	t_player		*player;
	uint8_t			*key_tab;
	t_ilx_texture	*test;
	t_ilx_texture	*north_texture;
	t_ilx_texture	*south_texture;
	t_ilx_texture	*east_texture;
	t_ilx_texture	*west_texture;
	uint32_t		*texure_buffer;
	t_ray			ray;
}	t_data;

t_rectangle	player_tile;

void	update_player_dir(t_player *player)
{
	player->dir.x = sinf(player->angle);
	player->dir.y = cosf(player->angle);
}

void	update_player_plane(t_player *player)
{
	player->plane.x = sinf(player->angle + M_PI_2);
	player->plane.y = cosf(player->angle + M_PI_2);
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
	tile.width = SCALE;
	tile.height = SCALE;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		tile.y = SCALE * i;
		while (j < MAP_WIDTH)
		{
			tile.x = SCALE * j;
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

void	draw_player(t_ilx *ilx, t_player *player)
{
	t_line	direction;
	t_line	plane;

	direction = ilx_set_line(player->pos.x , player->pos.y, player->pos.x + 20.0f * player->dir.x, player->pos.y + 20.0f * player->dir.y);
	ilx_draw_line(ilx->window, &direction, 1, 0xff0000);
	plane = ilx_set_line(player->pos.x -40.0f * player->plane.x, player->pos.y -40.0f * player->plane.y, player->pos.x + 40.0f * player->plane.x, player->pos.y + 40.0f * player->plane.y);
	ilx_draw_line(ilx->window, &plane, 1, 0xff0000);
	player_tile.height = 10;
	player_tile.width = 10;
	player_tile.x = player->pos.x - 5.0f;
	player_tile.y = player->pos.y - 5.0f;
	ilx_draw_fill_rect(ilx->window, &player_tile, 0xff0000);
}

void	move(t_data *data, float value, float angle_offset)
{
	float	x_step;
	float	y_step;
	float	x_offset;
	float	y_offset;
	
	x_step = data->player->pos.x + sinf(data->player->angle + angle_offset) * value;
	y_step = data->player->pos.y + cosf(data->player->angle + angle_offset) * value;
	if (x_step < data->player->pos.x)
		x_offset = -0.17f * SCALE;
	else
		x_offset = 0.17f * SCALE;
	if (y_step < data->player->pos.y)
		y_offset = -0.17f * SCALE;
	else
		y_offset = 0.17f * SCALE;
	if (!data->map[((int)(y_step + y_offset) / SCALE)][((int)(data->player->pos.x + x_offset) / SCALE)]
		&& !data->map[((int)(y_step + y_offset) / SCALE)][((int)(data->player->pos.x - x_offset) / SCALE)])
		data->player->pos.y = y_step;
	if (!data->map[((int)(data->player->pos.y + y_offset) / SCALE)][((int)(x_step + x_offset) / SCALE)]
		&& !data->map[((int)(data->player->pos.y - y_offset) / SCALE)][((int)(x_step + x_offset) / SCALE)])
		data->player->pos.x = x_step;
}

void	move_player(t_data *data)
{
	if (data->key_tab[0] == 1)
		data->player->angle -= 0.03f;
	else if (data->key_tab[1] == 1)
		data->player->angle += 0.03f;
	if (data->key_tab[2] && data->key_tab[4])
	{
		move(data, 0.042f * SCALE, 0.0f);
		move(data, 0.042f * SCALE, M_PI_2);
		return ;
	}
	if (data->key_tab[2] && data->key_tab[5])
	{
		move(data, 0.042f * SCALE, 0.0f);
		move(data, -0.042f * SCALE, M_PI_2);
		return ;
	}
	if (data->key_tab[3] && data->key_tab[4])
	{
		move(data, -0.042f * SCALE, 0.0f);
		move(data, 0.042f * SCALE, M_PI_2);
		return ;
	}
	if (data->key_tab[3] && data->key_tab[5])
	{
		move(data, -0.042f * SCALE, 0.0f);
		move(data, -0.042f * SCALE, M_PI_2);
		return ;
	}
	if (data->key_tab[2] == 1)
		move(data, 0.1f * SCALE, 0.0f);
	if (data->key_tab[3] == 1)
		move(data, -0.1f * SCALE, 0.0f);
	if (data->key_tab[4] == 1)
		move(data, 0.1f * SCALE, M_PI_2);
	if (data->key_tab[5] == 1)
		move(data, -0.1f * SCALE, M_PI_2);
}

void	print_input(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		printf("%d ", data->key_tab[i]);
	printf("\n");
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

void	update_ray(t_data *data)
{
	int				i;
	int				y;
	int				hit;
	int				side;
	float			x_view;
	float			wall_dist;
	float			wall_x;
	int				start;
	int				end;
	int				wall_size;
	t_ilx_texture	*current_texture;
	uint32_t		*texture_addr;
	int				texture_x;
	int				texture_y;
	float			texture_step;
	float			texture_pos;
	int				texture_height;
	t_line			ray_c;

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
			if (data->map[(int)data->ray.pos.y / SCALE][(int)data->ray.pos.x / SCALE])
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
		wall_x -= (float)floor((float)wall_x);
		//ray_c.p1.x = data->player->pos.x;
		//ray_c.p1.y = data->player->pos.y;
		//ray_c.p2.x = data->ray.pos.x;
		//ray_c.p2.y = data->ray.pos.y;
		//ilx_draw_line(data->ilx->window, &ray_c, 1, 0xff0000);
		wall_size = (int)((WIN_HEIGHT / wall_dist) * (float)SCALE);
		//printf("x : %d wall_size : %d wall_dist : %f\n", i, wall_size, wall_dist);
		start = (-wall_size >> 1) + (WIN_HEIGHT >> 1);
		if (start < 0)
			start = 0;
		end = (wall_size >> 1) + (WIN_HEIGHT >> 1);
		if (end >= WIN_HEIGHT)
			end = WIN_HEIGHT - 1;
		ray_c.p1.x = data->ilx->window->win_width - i - 1;
		ray_c.p2.x = data->ilx->window->win_width - i - 1;
		ray_c.p1.y = end;
		ray_c.p2.y = start;
		//if (side == 1)
		//	ilx_draw_line_vertical(data->ilx->window, start, end, data->ilx->window->win_width - i - 1, 0xff0000);
		//else if (side == 2)
		//	ilx_draw_line_vertical(data->ilx->window, start, end, data->ilx->window->win_width - i - 1, 0xff00);
		//else if (side == 3)
		//	ilx_draw_line_vertical(data->ilx->window, start, end, data->ilx->window->win_width - i - 1, 0xffff00);
		//else
		//	ilx_draw_line_vertical(data->ilx->window, start, end, data->ilx->window->win_width - i - 1, 0xff);
		//if (side == 1)
		//	ilx_draw_line(data->ilx->window, &ray_c, 1, 0xff0000);
		//else if (side == 2)
		//	ilx_draw_line(data->ilx->window, &ray_c, 1, 0xff00);
		//else if (side == 3)
		//	ilx_draw_line(data->ilx->window, &ray_c, 1, 0xffff00);
		//else
		//	ilx_draw_line(data->ilx->window, &ray_c, 1, 0xff);
		if (side == 1)
		{
			texture_x = (int)(wall_x * (float)data->west_texture->w);
			texture_step = 1.0f * data->west_texture->w / wall_size;
			texture_height = data->west_texture->h;
			current_texture = data->west_texture;
		}
		else if (side == 2)
		{
			texture_x = (int)(wall_x * (float)data->south_texture->w);
			texture_step = 1.0f * data->south_texture->w / wall_size;
			texture_height = data->south_texture->h;
			current_texture = data->south_texture;
		}
		else if (side == 3)
		{
			texture_x = (int)(wall_x * (float)data->north_texture->w);
			texture_x = data->north_texture->w - texture_x - 1;
			texture_step = 1.0f * data->north_texture->w / wall_size;
			texture_height = data->north_texture->h;
			current_texture = data->north_texture;
		}
		else
		{
			texture_x = (int)(wall_x * (float)data->east_texture->w);
			texture_x = data->east_texture->w - texture_x - 1;
			texture_step = 1.0f * data->east_texture->w / wall_size;
			texture_height = data->east_texture->h;
			current_texture = data->east_texture;
		}
		texture_pos = (start - data->ilx->window->win_height / 2 + wall_size / 2) * texture_step;
		y = start;
		texture_addr = (uint32_t *)current_texture->addr;
		while (y < end)
		{
			texture_y = (int)texture_pos & (texture_height - 1);
			texture_pos += texture_step;
			data->texure_buffer[y - start] = texture_addr[texture_height * texture_y + (current_texture->h - 1 - texture_x)];
			y++;
		}
		ilx_draw_texture_line(data->ilx->window, &ray_c, 1, data->texure_buffer);
		i++;
	}
}

void	draw_background(t_window *window, uint32_t color_ceiling, uint32_t color_floor)
{
	int	i;
	int	max;
	int	max2;
	
	i = 0;
	max2 = window->win_height * window->win_width;
	max = max2 >> 1;
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
	//draw_map(data->map, data->ilx);
	update_ray(data);
	//draw_player(data->ilx, data->player);
	ilx_draw_texture(data->ilx->window, 5, 5, data->test);
	ilx_draw_gui(data->ilx, data->current_gui);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);

	frame_time = get_frame_time(prev_time);
    time = (float)frame_time / 1000000.0;
    fps = 1 / time;
	fps_str = ft_itoa(fps);
	mlx_string_put(data->ilx->mlx, data->ilx->window->window, 5, 15, 0, fps_str);
	free(fps_str);
	//printf("%d\n", fps);
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

	player.pos.x = 5.0f * SCALE;
	player.pos.y = 5.0f * SCALE;
	player.angle = M_PI_2;
	map = create_map();
	ilx = ilx_init(); 
	ilx.window = ilx_create_window(&ilx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	test = ilx_create_gui();

	data.clic = 0;
	data.enable_input = 1;
	data.current_gui = NULL;
	data.map = map;
	data.player = &player;
	data.gui = test;
	data.ilx = &ilx;
	data.test = ilx_create_texture(data.ilx, "assets/rocket.xpm");
	data.north_texture = ilx_create_texture(data.ilx, "assets/bluestone.xpm");
	data.south_texture = ilx_create_texture(data.ilx, "assets/eagle.xpm");
	data.west_texture = ilx_create_texture(data.ilx, "assets/redbrick.xpm");
	data.east_texture = ilx_create_texture(data.ilx, "assets/wood.xpm");
	data.texure_buffer = malloc(sizeof(uint32_t) * data.ilx->window->win_height);
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
	mlx_hook(ilx.window->window, ON_KEYUP, 1L << 1, ft_up_key, &data);
	mlx_loop(ilx.mlx);

	return (0);
}
