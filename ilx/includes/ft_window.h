/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:00:51 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/20 21:58:57 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WINDOW_H
# define FT_WINDOW_H

# include <stdlib.h>
# include <stdio.h>
# include "ilx.h"
# include "libft.h"

typedef struct s_ilx	t_ilx;

typedef struct s_window
{
	void			*window;
	char			*win_name;
	void			*img;
	char			*addr;
	unsigned int	*renderer;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				win_width;
	int				win_height;
}	t_window;

t_window	*ft_new_window(void *win, char *win_name);
t_window	*ilx_create_window(t_ilx *ilx, int x, int y, char *win_name);
void		ilx_put_img_to_window(t_ilx *ilx);
void		ilx_clear_window(t_window *window, uint32_t color);
t_ilx		ilx_init(void);

#endif