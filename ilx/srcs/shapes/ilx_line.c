/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:38:46 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/02 12:26:38 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"
#include <math.h>

t_line	*ilx_create_line(float x1, float y1, float x2, float y2)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->p1.x = x1;
	line->p1.y = y1;
	line->p2.x = x2;
	line->p2.y = y2;
	return (line);
}

t_line	ilx_set_line(float x1, float y1, float x2, float y2)
{
	t_line	line;

	line.p1.x = x1;
	line.p1.y = y1;
	line.p2.x = x2;
	line.p2.y = y2;
	return (line);
}

void	ilx_draw_line(t_window *win, t_line *line, int size, uint32_t colors)
{
	t_line	ln;
	float	x;
	float	y;
	float	step;
	int		i;

	(void)size;
	ln.p1.x = (line->p2.x - line->p1.x);
	ln.p1.y = (line->p2.y - line->p1.y);
	if (fabsf(ln.p1.x) >= fabsf(ln.p1.y))
		step = fabsf(ln.p1.x);
	else
		step = fabsf(ln.p1.y);
	ln.p1.x /= step;
	ln.p1.y /= step;
	x = line->p1.x;
	y = line->p1.y;
	i = 0;
	while (i <= step)
	{
		win->renderer[((int)x + (int)y * win->win_width)] = colors;
		x += ln.p1.x;
		y += ln.p1.y;
		i++;
	}
}

void	ilx_draw_texture_line(t_window *win, t_line *line, int size,
	uint32_t *colors)
{
	t_line	ln;
	float	x;
	float	y;
	float	step;
	int		i;

	(void)size;
	ln.p1.x = (line->p2.x - line->p1.x);
	ln.p1.y = (line->p2.y - line->p1.y);
	if (fabsf(ln.p1.x) >= fabsf(ln.p1.y))
		step = fabsf(ln.p1.x);
	else
		step = fabsf(ln.p1.y);
	ln.p1.x /= step;
	ln.p1.y /= step;
	x = line->p1.x;
	y = line->p1.y;
	i = -1;
	while (++i <= step)
	{
		win->renderer[((int)x + (int)y * win->win_width)]
			= colors[(int)step - i - 1];
		x += ln.p1.x;
		y += ln.p1.y;
	}
}
