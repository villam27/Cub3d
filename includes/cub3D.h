/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:48:05 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/28 12:16:56 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ilx.h"
# include "utils.h"
# include "gui.h"
# include "ilx_texture.h"
# include "key_binding.h"
# include "raycasting.h"
# include "player.h"
# include "data.h"
# include "quit.h"

# include <sys/time.h>
# include <string.h>

# define MAP_WIDTH 20
# define MAP_HEIGHT 20

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

void	ilx_change_button_color(t_data *data);
void	draw_background(t_window *window, uint32_t color_ceiling,
			uint32_t color_floor);

#endif
