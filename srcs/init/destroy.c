/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:13:05 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/16 09:30:37 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_everything(t_data *data)
{
	ilx_destroy_texture(data->ilx, data->west_texture);
	ilx_destroy_texture(data->ilx, data->north_texture);
	ilx_destroy_texture(data->ilx, data->south_texture);
	ilx_destroy_texture(data->ilx, data->east_texture);
	ilx_destroy_texture(data->ilx, data->floor_texture);
	ilx_destroy_texture(data->ilx, data->ceiling_texture);
	ilx_destroy_texture(data->ilx, data->gun_texture);
	ilx_destroy_gui(data->gui);
	if (data->map_data)
		free_map(data->map, data->map_data->h);
	free(data->key_tab);
	free(data->z_buffer);
	free(data->map_data);
	free(data->player);
	ilx_destroy_window(data->ilx);
	free(data);
}

void	ilx_err(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
