/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:47:38 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 15:04:30 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub_math.h"

typedef struct s_ray
{
	t_vec2d	dir;
	t_vec2d	delta;
	t_vec2d	dist;
	t_vec2d	step;
	t_vec2d	pos;
}	t_ray;

#endif