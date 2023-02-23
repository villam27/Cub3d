/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx_texture.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:47:49 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/23 10:01:40 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILX_TEXTURE_H
# define ILX_TEXTURE_H

# include "ilx.h"

typedef struct s_ilx_texture
{
	void		*img;
	char		*addr;
	int			bits_per_px;
	int			line_len;
	int			endian;
	int			w;
	int			h;
	int			scale_x;
	int			scale_y;
	int			flip;
	uint32_t	*buffer;
}	t_ilx_texture;

t_ilx_texture	*ilx_create_texture(t_ilx *ilx, char *path);
void			ilx_draw_texture(t_window *win, int x, int y,
					t_ilx_texture *tex);
/*void			ilx_render_copy(t_window *win, t_ilx_texture *tex,
					t_ilx_point *pos, t_ilx_rect *rec);*/
void			ilx_destroy_texture(t_ilx *ilx, t_ilx_texture *texture);

#endif