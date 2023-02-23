/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_shapes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:09:16 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/23 14:26:10 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILX_SHAPES_H
# define ILX_SHAPES_H

# include <stdint.h>

typedef struct s_window	t_window;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_line
{
	t_point	p1;
	t_point	p2;
}	t_line;

typedef struct s_rectangle
{
	float	x;
	float	y;
	float	width;
	float	height;
}	t_rectangle;

typedef struct s_circle
{
	float	radius;
	int		points;
}	t_cicle;

t_point		*ilx_create_point(float x, float y);
t_point		ilx_new_point(float x, float y);

/* Deprecated. Use this function only if you really have to.
   Use the renderer in the window structure like
   win.renderer[x + y * win_width] for better performance*/
void		ilx_pixel_put(t_window *win, int x, int y, uint32_t color);

t_rectangle	*ilx_create_rect(float x, float y, float w, float h);
t_rectangle	ilx_new_rect(float x, float y, float w, float h);
void		ilx_draw_fill_rect(t_window *win, t_rectangle *rect,
				uint32_t colors);
void		ilx_draw_rect(t_window *win, t_rectangle *rect, uint32_t colors);

t_line		*ilx_create_line(float x1, float y1, float x2, float y2);
t_line		ilx_set_line(float x1, float y1, float x2, float y2);
void		ilx_draw_line(t_window *win, t_line *line,
				int size, uint32_t colors);
void		ilx_draw_texture_line(t_window *win, t_line *line,
				int size, uint32_t *colors);
void		ilx_draw_line_vertical(t_window *win, int start,
				int end, int x, uint32_t *colors);

t_cicle		*ilx_create_circle(float radius, int points);
t_cicle		ilx_new_circle(float radius, int points);
void		ilx_draw_circle(t_cicle circle, uint32_t colors);

#endif