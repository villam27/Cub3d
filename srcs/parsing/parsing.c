/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/01 19:26:32 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "fcntl.h"

int	get_id(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (1);
	if (!ft_strncmp(line, "SO", 2))
		return (2);
	if (!strncmp(line, "WE", 2))
		return (3);
	if (!strncmp(line, "EA", 2))
		return (4);
	if (!strncmp(line, "F", 1))
		return (5);
	if (!strncmp(line, "C", 1))
		return (6);
	return (0);
}

void	set_id(int id, t_data *map_data, char *line)
{
	line[ft_strlen(line) - 1] = 0;
	if (id == 1)
		map_data->north_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == 2)
		map_data->south_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == 3)
		map_data->west_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == 4)
		map_data->east_texture = ilx_create_texture(map_data->ilx, line + 3);
	ft_printf("%s", line + 3);
}

int	check_data_integrity(t_map_data *map_data)
{
	(void)map_data;
	return (0);
}

t_map_data	*get_map_data(char *path, t_data *data)
{
	int			fd_map;
	t_map_data	*map_data;
	char		*line;
	int			id;

	map_data = malloc(sizeof(t_map_data));
	if (!map_data)
		return (NULL);
	fd_map = open(path, O_RDONLY);
	line = get_next_line(fd_map);
	id = -1;
	while (id != 0)
	{
		id = get_id(line);
		if (id)
		{
			set_id(id, data, line);
			free(line);
			line = get_next_line(fd_map);
		}
	}
	if (!check_data_integrity(map_data))
		return (free(line), NULL); //free all
	/*
	else
		get w and h
	*/
	return (map_data);
}

int	load_maps(t_data *data, char *path)
{
	//t_map_data	*map_data;
	get_map_data(path, data);
//	map_data = get_map_data(path);
	return (1);
}
