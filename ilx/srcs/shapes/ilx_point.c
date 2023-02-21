/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:38:50 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/21 11:29:45 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"

t_point	*ilx_create_point(float x, float y)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

t_point	ilx_new_point(float x, float y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	ilx_pixel_put(t_window *win, int x, int y, uint32_t color)
{
	char	*dst;

	if (x >= 0 && x < win->win_width && y >= 0 && y < win->win_height)
	{
		dst = win->addr + (y * win->line_length + x
				* (win->bits_per_pixel >> 3));
		*(unsigned int *)dst = color;
	}
}
