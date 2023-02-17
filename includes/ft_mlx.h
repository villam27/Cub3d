/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:38:20 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/05 22:30:01 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "libft.h"
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include "mlx_keycodes.h"
# ifdef __gnu_linux__
#  include "mlx.h"
# else
#  include "mlx/mlx.h"
# endif

# define FILL 42
# define LINE 43
# define WIN_WIDTH 1920
# define WIN_HEIGTH 1080

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/*	origin in the upper left
	corner */

typedef struct s_rectangle
{
	int	x;
	int	y;
	int	width;
	int	heigth;
}	t_rectangle;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_bgra
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}	t_bgra;

typedef union u_color
{
	int32_t		color;
	uint32_t	ucolor;
	t_bgra		tcolor;
}	t_color;

typedef struct s_line
{
	t_point	p1;
	t_point	p2;
	t_color	color_p1;
	t_color	color_p2;
}	t_line;

typedef struct s_step
{
	int	step_x;
	int	step_y;
}	t_step;

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
	t_color	color;
}	t_vec3d;

typedef struct s_4x4_matrix
{
	float	matrix[4][4];
}	t_4x4_matrix;

typedef struct s_proj_vars
{
	float	clip_start;
	float	clip_end;
	float	fov;
	float	fov_rad;
	float	aspect_ratio;
}	t_proj_vars;

typedef struct s_mlx_vars
{
	void			*mlx;
	void			*win;
	t_data			img;
	char			lock;
	t_vec3d			**map;
	t_vec3d			**map_rotate;
	t_vec3d			**map_proj;
	int				nb_x;
	int				nb_y;
	t_line			*edges;
	t_4x4_matrix	proj_matrix;
	t_4x4_matrix	iso_matrix;
	t_4x4_matrix	rotation_matrix;
	t_vec3d			rotation_vars;
	t_vec3d			scale;
	t_proj_vars		proj_vars;
	uint8_t			color_render;
	uint8_t			draw_mode;
	int				nb_edges;
	t_rectangle		border;
	uint8_t			proj_mode;
	uint8_t			opti_move;
	t_vec3d			translate;
	uint8_t			move;
	uint8_t			display_info;
	t_rectangle		info;
	char			*nb_edges_str;
	char			*nb_point_str;
}	t_mlx_vars;

typedef struct s_set_edges_var
{
	int	i;
	int	reverse;
	int	x;
	int	y;
}	t_set_edges_var;

void		ft_mlx_pixel_put(t_data *data, int x, int y, uint32_t color);
uint32_t	ft_mlx_get_pixel(t_data *data, int x, int y);
t_step		ft_set_step(t_point *p1, t_point *p2);
void		ft_draw_hor(t_data *data, t_line *line, uint32_t color);
void		ft_draw_ver(t_data *data, t_line *line, uint32_t color);
void		ft_draw_hor_gradient(t_data *data, t_line *line,
				uint32_t color_from, uint32_t color_to);
void		ft_draw_ver_gradient(t_data *data, t_line *line,
				uint32_t color_from, uint32_t color_to);
uint32_t	ft_set_next_color(uint32_t color_from, uint32_t color_to,
				t_line *line, t_point *point);
t_point		ft_init_point(t_point *p1);
char		ft_mlx_draw_rectangle(t_data *data, t_rectangle *rect,
				uint32_t color,
				char disp_mod);
void		ft_mlx_draw_line(t_data *data, t_line *line, uint32_t color);
void		ft_mlx_draw_line_gradient(t_data *data, t_line *line,
				uint32_t color_from, uint32_t color_to);
void		ft_mlx_set_background(t_data *data, int win_w, int win_h,
				uint32_t color);
int			ft_line_clip(uint8_t codes[2], t_line *line, t_rectangle b);
uint8_t		ft_out_code(t_rectangle b, t_point p);
void		ft_init_proj_matrix(t_proj_vars *proj_vars, t_4x4_matrix *matrix);
void		ft_init_iso_matrix(t_proj_vars *proj_vars, t_4x4_matrix *matrix);
void		ft_init_rot_matrix(t_vec3d *rot_vars, t_4x4_matrix *matrix);
int			ft_up_key(int keycode, t_mlx_vars *vars);
void		ft_free_map(t_vec3d **map, int nb_elements);
void		ft_free_all_maps(t_mlx_vars *vars);
t_vec3d		**ft_fill_map(t_vec3d **map, int fd);
int			ft_init_vars(t_mlx_vars *vars, char *map_name);
int			ft_read_map_file(char *map_name, int *nb_x, int *nb_y,
				t_mlx_vars *vars);
void		ft_fill(char **tab, int y, t_vec3d **map);
void		ft_init_proj_vars(t_proj_vars *proj_vars);
void		ft_get_map_size(int *nb_x, int *nb_y, int fd);
void		ft_proj_map(t_mlx_vars *vars);
int			ft_render_next_frame(t_mlx_vars *vars);
t_line		*ft_set_edges(t_mlx_vars *vars);
int			ft_clipping_line(uint8_t *codes, t_mlx_vars *vars, int *i);
int			ft_press_key(int keycode, t_mlx_vars *vars);
void		ft_press_key_up(int keycode, t_mlx_vars *vars);
void		ft_press_key_move(int keycode, t_mlx_vars *vars);
void		ft_press_key_l(int keycode, t_mlx_vars *vars);
void		ft_press_key_p(int keycode, t_mlx_vars *vars);
int			ft_close(t_mlx_vars *vars);
int			ft_get(int x, int y, t_mlx_vars *vars);
int			ft_set_rotate_on(int button, int x, int y, t_mlx_vars *vars);
int			ft_set_rotate_off(int button, int x, int y, t_mlx_vars *vars);

#endif
