/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:28:49 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 15:01:38 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "gui.h"
# include "ilx_texture.h"
# include "raycasting.h"

typedef struct s_player	t_player;

typedef struct s_data
{
	t_ilx			*ilx;
	t_gui			*gui;
	uint8_t			clic;
	uint8_t			enable_input;
	t_gui			*current_gui;
	int				**map;
	t_player		*player;
	uint8_t			*key_tab;
	t_ilx_texture	*north_texture;
	t_ilx_texture	*south_texture;
	t_ilx_texture	*east_texture;
	t_ilx_texture	*west_texture;
	uint32_t		*texure_buffer;
	t_ray			ray;
}	t_data;

#endif