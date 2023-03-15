/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:38:50 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/15 19:42:34 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"

uint32_t	ilx_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

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
