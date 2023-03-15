/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:48:05 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/15 20:34:36 by alboudje         ###   ########.fr       */
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

# define WIN_WIDTH 1200
# define WIN_HEIGHT 720

# define NORMAL_SPEED 6.0f
# define SPRINT_SPEED 10.0f
# define SNEAK_SPEED 4.0f
# define PLAYER_SPAWN_OFFSET 0.5f

enum e_map_value
{
	FLOOR = 0,
	WALL = 1,
	NOTHING = 2,
	CHECKED = 9
};

enum e_map_identifier
{
	EMPTY_LINE = -1,
	NO_ID,
	NO,
	SO,
	WE,
	EA,
	FL,
	CE,
	FT,
	CT
};

enum
{
	SUCCESS,
	ERROR
};

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

typedef struct s_map_data
{
	int				w;
	int				h;
	int				closed;
	t_ivec2d		player_pos;
	char			direction;
}	t_map_data;

typedef struct s_data
{
	t_ilx			*ilx;
	t_gui			*gui;
	uint8_t			clic;
	uint8_t			enable_input;
	t_gui			*current_gui;
	t_map_data		*map_data;
	int				**map;
	t_player		*player;
	uint8_t			*key_tab;
	t_ilx_texture	*north_texture;
	t_ilx_texture	*south_texture;
	t_ilx_texture	*east_texture;
	t_ilx_texture	*west_texture;
	t_ilx_texture	*floor_texture;
	t_ilx_texture	*ceiling_texture;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	t_ray			ray;
	float			*z_buffer;
	int				prev_x;
	t_minimap		minimap;
}	t_data;

void		ilx_change_button_color(t_data *data);

void		draw_textured_background(t_data *data);
void		draw_background(t_window *window, uint32_t color_ceiling,
				uint32_t color_floor);

void		update_player_dir(t_player *player);
void		update_player_plane(t_player *player);
int			rotate(int x, int y, t_data *data);
int			move_mouse(void *param);
void		move(t_data *data, float value, float angle_offset);
void		move_player(t_data *data, float delta);

void		update_ray(t_data *data);


int			init_all(t_data *data, char *map_path);
t_data		*create_data(void);
void		destroy_everything(t_data *data);
void		init_ray_val(t_data *data, t_raycast *raycast, int i);
void		init_step_ray(t_data *data);
void		update_ray(t_data *data);
int			on_clic(int key, int x, int y, t_data *data);
int			on_release(int key, int x, int y, t_data *data);
int			ft_press_key(int keycode, t_data *data);
int			ft_up_key(int keycode, t_data *data);

long		get_frame_time(long start_time);
long		get_start_time(void);

void		print_map(int **map, int w, int h);
void		free_map(int **map, int h);
int			get_player_pos(char *line, t_map_data *map_data);
int			get_id(char *line);
int 		*set_line(char *line, int len);
int			check_data_integrity(t_data *data);
int			**copy_map(int **map, t_map_data *map_data);
t_map_data	*get_map_data(char *path, t_data *data);
int			load_maps(t_data *data, char *path);
int			set_color(uint32_t *color, char *line);
int			set_texture(t_ilx_texture **texture, t_data *data, char *line);
int			set_id(int id, t_data *map_data, char *line);

void		*start(void *param);
void		*quit(void *param);
void		ilx_destroy_window(t_ilx *ilx);
void		destroy_everything(t_data *data);
int			cross_quit(void *param);

#endif
