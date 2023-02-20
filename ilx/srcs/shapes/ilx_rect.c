/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:38:48 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/15 16:19:40 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"

t_rectangle	*ilx_create_rect(float x, float y, float w, float h)
{
	t_rectangle	*rect;

	rect = malloc(sizeof(t_rectangle));
	if (!rect)
		return (NULL);
	rect->x = x;
	rect->y = y;
	rect->width = w;
	rect->height = h;
	return (rect);
}

t_rectangle	ilx_new_rect(float x, float y, float w, float h)
{
	t_rectangle	rect;

	rect.x = x;
	rect.y = y;
	rect.width = w;
	rect.height = h;
	return (rect);
}

void	ilx_draw_fill_rect(t_window *win, t_rectangle *rect, uint32_t colors)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect->height)
	{
		j = 0;
		while (j < rect->width)
		{
			ilx_pixel_put(win, j + rect->x, i + rect->y, colors);
			j++;
		}
		i++;
	}
}

void	ilx_draw_rect(t_window *win, t_rectangle *rect, uint32_t colors)
{
	t_line	l1;
	t_line	l2;
	t_line	l3;
	t_line	l4;

	l1 = ilx_set_line(rect->x, rect->y, rect->x + rect->width, rect->y);
	l2 = ilx_set_line(rect->x, rect->y, rect->x, rect->y + rect->height);
	l3 = ilx_set_line(rect->x + rect->width, rect->y,
			rect->x + rect->width, rect->y + rect->height);
	l4 = ilx_set_line(rect->x, rect->y + rect->height,
			rect->x + rect->width, rect->y + rect->height);
	ilx_draw_line(win, &l1, 1, colors);
	ilx_draw_line(win, &l2, 1, colors);
	ilx_draw_line(win, &l3, 1, colors);
	ilx_draw_line(win, &l4, 1, colors);
}
