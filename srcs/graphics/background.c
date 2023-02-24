/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:07:31 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 14:19:42 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_background(t_window *window, uint32_t color_ceiling,
			uint32_t color_floor)
{
	//int	i;
	int	max;
	int	max2;

	max2 = window->win_height * window->win_width;
	max = max2 >> 1;
	//i = 0;
	//while (i < max)
	//{
	//	window->renderer[i] = color_ceiling;
	//	i++;
	//}
	//while (i < max2)
	//{
	//	window->renderer[i] = color_floor;
	//	i++;
	//}
	memset((uint32_t *)window->renderer, color_ceiling, sizeof(uint32_t) * max);
	memset((uint32_t *)&window->renderer[max], color_floor, sizeof(uint32_t) * max);
}
