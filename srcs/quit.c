/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:29:43 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/12 13:17:26 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ilx_destroy_window(t_ilx *ilx)
{
	if (!ilx)
		return ;
	mlx_destroy_image(ilx->mlx, ilx->window->img);
	mlx_destroy_window(ilx->mlx, ilx->window->window);
	free(ilx->mlx);
	free(ilx->window->win_name);
	free(ilx->window);
	free(ilx);
}

void	*quit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	destroy_everything(data);
	exit (0);
}

void	*start(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_mouse_hide(data->ilx->mlx, data->ilx->window->window);
	data->current_gui = NULL;
	return (NULL);
}

int	cross_quit(void *param)
{
	quit(param);
	return (0);
}
