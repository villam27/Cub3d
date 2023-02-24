/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:29:43 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 15:30:52 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "quit.h"

static void	ilx_destroy_window(t_ilx *ilx)
{
	mlx_destroy_image(ilx->mlx, ilx->window->img);
	mlx_destroy_window(ilx->mlx, ilx->window->window);
	free(ilx->window->win_name);
	free(ilx->window);
}

void	*quit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ilx_destroy_window(data->ilx);
	mlx_destroy_display(data->ilx->mlx);
	ilx_destroy_gui(data->gui);
	free(data->ilx->mlx);
	exit (0);
}

int	cross_quit(void *param)
{
	quit(param);
	return (0);
}
