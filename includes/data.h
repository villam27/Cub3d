/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:28:49 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/28 17:17:53 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "gui.h"
# include "ilx_texture.h"
# include "raycasting.h"

typedef struct s_player	t_player;

/*
	TODO: Remove test variables
*/
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
	t_ilx_texture	*test_texutre;
	t_point			test_pts;
	t_rectangle		test_rect;
	t_ray			ray;
	int				prev_x;
}	t_data;

#endif