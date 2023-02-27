/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:47:35 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/25 19:32:11 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub_math.h"
# include "data.h"

typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	float	angle;
}	t_player;

void	update_player_dir(t_player *player);
void	update_player_plane(t_player *player);
int		rotate(int x, int y, t_data *data);
int		move_mouse(void *param);
void	move(t_data *data, float value, float angle_offset);
void	move_player(t_data *data);

#endif