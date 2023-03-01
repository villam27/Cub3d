/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:24:51 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 11:25:09 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_player_dir(t_player *player)
{
	player->dir.x = sinf(player->angle);
	player->dir.y = cosf(player->angle);
}

void	update_player_plane(t_player *player)
{
	player->plane.x = sinf(player->angle + M_PI_2);
	player->plane.y = cosf(player->angle + M_PI_2);
}
