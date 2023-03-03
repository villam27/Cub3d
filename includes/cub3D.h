/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:48:05 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/02 15:47:29 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ilx.h"
# include "utils.h"
# include "gui.h"
# include "ilx_texture.h"

# include <sys/time.h>
# include <math.h>
# include <float.h>
# include <string.h>

# define MAP_WIDTH 20
# define MAP_HEIGHT 20

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720

typedef struct s_vec2d
{
	float	x;
	float	y;
}	t_vec2d;

typedef struct s_ivec2d
{
	int	x;
	int	y;
}	t_ivec2d;

typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	float	angle;
	float	player_speed;
	float	normal_speed;
	float	sprint_speed;
	float	sneak_speed;
	float	rotation_speed;
}	t_player;

typedef struct s_ray
{
	t_vec2d	dir;
	t_vec2d	delta;
	t_vec2d	dist;
	t_vec2d	step;
	t_vec2d	pos;
}	t_ray;

typedef struct s_minimap
{
	t_rectangle	background;
}	t_minimap;

typedef struct s_raycast
{
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
}	t_raycast;

typedef struct s_backgound
{
	t_vec2d		ray_dir_1;
	t_vec2d		ray_dir_2;
	t_vec2d		step;
	t_vec2d		floor_pos;
	t_ivec2d	cell;
	t_ivec2d	f_texture_coord;
	int			horizon;
	float		camera_z;
	float		camera_dist;
	uint32_t	*floor;
	uint32_t	*ceiling;
}	t_background;

/*
	TODO: Remove test variables
*/
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
	t_ilx_texture	*north_texture;
	t_ilx_texture	*south_texture;
	t_ilx_texture	*east_texture;
	t_ilx_texture	*west_texture;
	t_ilx_texture	*floor_texture;
	t_ilx_texture	*ceiling_texture;
	t_ilx_texture	*test_texutre;
	t_point			test_pts;
	t_rectangle		test_rect;
	t_ray			ray;
	float			*z_buffer;
	int				prev_x;
	t_minimap		minimap;
}	t_data;

void	ilx_change_button_color(t_data *data);

void	draw_textured_background(t_data *data);
void	draw_background(t_window *window, uint32_t color_ceiling,
			uint32_t color_floor);

void	update_player_dir(t_player *player);
void	update_player_plane(t_player *player);
int		rotate(int x, int y, t_data *data);
int		move_mouse(void *param);
void	move(t_data *data, float value, float angle_offset);
void	move_player(t_data *data, float delta);

void	init_ray_val(t_data *data, t_raycast *raycast, int i);
void	init_step_ray(t_data *data);
void	update_ray(t_data *data);

int		on_clic(int key, int x, int y, t_data *data);
int		on_release(int key, int x, int y, t_data *data);
int		ft_press_key(int keycode, t_data *data);
int		ft_up_key(int keycode, t_data *data);

long	get_frame_time(long start_time);
long	get_start_time(void);

void	*quit(void *param);
int		cross_quit(void *param);

#endif
