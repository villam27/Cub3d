/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 00:38:48 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/21 22:17:51 by lcrimet          ###   ########lyon.fr   */
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

void	ilx_draw_fill_rect(t_window *win, t_rectangle *rect, uint32_t color)
{
	int				i;
	int				j;

	i = 0;
	while (i < rect->height)
	{
		j = 0;
		while (j < rect->width)
		{
			//ilx_pixel_put(win, j + rect->x, i + rect->y, color);
			//if (i == 0 && j == 0)
			//	printf("%p\n", &img[j + (int)rect->x + (i + (int)rect->y) * WIN_WIDTH]);
			win->renderer[(j + (int)rect->x + (i + (int)rect->y) * win->win_width)] = color;
			j++;
		}
		i++;
	}
}

void	ilx_draw_rect(t_window *win, t_rectangle *rect, uint32_t color)
{
	int				i;
	int				j;

	i = 0;
	while (i < rect->height)
	{
		j = 0;
		while (j < rect->width)
		{
			if (j == 1 && i != 0 && i != rect->height - 1)
				j = rect->width - 1;
			//ilx_pixel_put(win, j + rect->x, i + rect->y, color);
			//if (i == 0 && j == 0)
			//	printf("%p\n", &img[j + (int)rect->x + (i + (int)rect->y) * WIN_WIDTH]);
			win->renderer[(j + (int)rect->x + (i + (int)rect->y) * WIN_WIDTH)] = color;
			j++;
		}
		i++;
	}
}
