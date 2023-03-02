/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:47:14 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/02 12:21:58 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx_texture.h"

t_ilx_texture	*ilx_create_texture(t_ilx *ilx, char *path)
{
	t_ilx_texture	*sprite;

	sprite = malloc(sizeof(t_ilx_texture));
	if (!sprite)
		return (NULL);
	sprite->img = mlx_xpm_file_to_image(ilx->mlx, path,
			&sprite->w, &sprite->h);
	if (!sprite->img)
		return (free(sprite), NULL);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_px,
			&sprite->line_len, &sprite->endian);
	if (!sprite->addr)
		return ((void)mlx_destroy_image(ilx->mlx, sprite->img), NULL);
	sprite->buffer = (uint32_t *)sprite->addr;
	sprite->flip = 0;
	sprite->scale_x = 1;
	sprite->scale_y = 1;
	return (sprite);
}

void	ilx_draw_texture(t_window *win, int x, int y,
			t_ilx_texture *tex)
{
	uint32_t	*src;
	int			i;
	int			j;
	int			i_w;
	int			i_y;

	i = 0;
	while (i < tex->h)
	{
		j = 0;
		i_w = i * tex->w;
		i_y = (i + y) * win->win_width + x;
		while (j < tex->w)
		{
			src = (tex->buffer + (i_w + j));
			if (*src != 0xff000000)
				win->renderer[i_y + j] = *src;
			j++;
		}
		i++;
	}
}

static void	ilx_render_px(t_window *win, t_ilx_texture *tex,
	t_rectangle *values)
{
	char		*dst;
	char		*src;

	dst = (win->addr + (((int)values->x) * win->line_length + ((int)values->y)
				*(win->bits_per_pixel >> 3)));
	src = (tex->addr + (((int)values->width) * tex->line_len
				+ ((int)values->height)
				*(tex->bits_per_px >> 3)));
	if (*(unsigned *)src != 0xff000000)
		*(unsigned long *)dst = *(unsigned long *)src;
}

void	ilx_render_copy(t_window *win, t_ilx_texture *tex,
			t_point *pos, t_rectangle *rec)
{
	int			i;
	int			j;
	t_rectangle	p;

	i = 0;
	while (i < rec->height)
	{
		j = 0;
		while (j < rec->width)
		{
			p = ilx_new_rect(pos->y + i, pos->x + j, rec->y + i, rec->x + j);
			if (tex->flip)
				p = ilx_new_rect(pos->y + i, pos->x + j, rec->y + i,
						rec->width + rec->x - j - 1);
			ilx_render_px(win, tex, &p);
			j++;
		}
		i++;
	}
}

void	ilx_destroy_texture(t_ilx *ilx, t_ilx_texture *texture)
{
	if (!texture)
		return ;
	mlx_destroy_image(ilx->mlx, texture->img);
	free(texture);
}
