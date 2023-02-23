/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:47:14 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/23 10:08:04 by lcrimet          ###   ########lyon.fr   */
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
	//char	*dst;
	uint32_t	*src;
	int			i;
	int			j;

	i = 0;
	while (i < tex->h)
	{
		j = 0;
		while (j < tex->w)
		{
			if (x < win->win_width && x >= 0 && y < win->win_height && y >= 0)
			{
				//dst = (win->addr + ((y + i) * win->line_length + (x + j)
				//			*(win->bits_per_pixel >> 3)));
				src = (tex->buffer + (i * tex->w + j));
				if (*src != 0xff000000)
					win->renderer[((y + i) * win->win_width + (x + j))] = *src;
			}
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
