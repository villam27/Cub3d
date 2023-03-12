/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:34:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/12 13:48:01 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "fcntl.h"

int	get_id(char *line)
{
	if (!line)
		return (NO_ID);
	if (line[0] == '\n')
		return (EMPTY_LINE);
	if (!ft_strncmp(line, "NO", 2))
		return (NO);
	if (!ft_strncmp(line, "SO", 2))
		return (SO);
	if (!strncmp(line, "WE", 2))
		return (WE);
	if (!strncmp(line, "EA", 2))
		return (EA);
	if (!strncmp(line, "F", 1))
		return (FL);
	if (!strncmp(line, "C", 1))
		return (CE);
	return (NO_ID);
}

t_map_data	*init_map_data(void)
{
	t_map_data	*map_data;

	map_data = malloc(sizeof(t_map_data));
	if (!map_data)
		return (NULL);
	map_data->w = 0;
	map_data->h = 0;
	return (map_data);
}

int	set_texture(t_ilx_texture **texture, t_data *data, char *line)
{
	if (*texture == NULL)
		*texture = ilx_create_texture(data->ilx, line + 3);
	else
		return (SUCCESS);
	return (ERROR);
}

int	set_id(int id, t_data *map_data, char *line)
{
	int	len;

	len = ft_strlen(line);
	line[len - 1] = 0;
	if (id == EMPTY_LINE)
		return (ERROR);
	if (id == NO)
		return (set_texture(&map_data->north_texture, map_data, line));
	if (id == SO)
		return (set_texture(&map_data->south_texture, map_data, line));
	if (id == WE)
		return (set_texture(&map_data->west_texture, map_data, line));
	if (id == EA)
		return (set_texture(&map_data->east_texture, map_data, line));
	if (id == FL)
		map_data->floor_texture = ilx_create_texture(map_data->ilx, line + 2);
	if (id == CE)
		map_data->ceiling_texture = ilx_create_texture(map_data->ilx, line + 2);
	return (ERROR);
}

/*
	TODO: fix line = NULL;
*/
t_map_data	*get_map_data(char *path, t_data *data)
{
	int			fd_map;
	t_map_data	*map_data;
	char		*line;
	int			id;

	fd_map = open(path, O_RDONLY);
	if (fd_map <= 0)
		return (NULL);
	map_data = init_map_data();
	if (!map_data)
		return (NULL);
	map_data->player_pos.x = -1;
	line = get_next_line(fd_map);
	id = EMPTY_LINE;
	while (id != NO_ID)
	{
		id = get_id(line);
		if (id)
		{
			if (!set_id(id, data, line))
				return (free(line), free(map_data), NULL);
			free(line);
			line = get_next_line(fd_map);
		}
	}
	if (check_data_integrity(data) == ERROR)
		return (free(line), free(map_data), NULL);
	while (line)
	{
		map_data->h += 1;
		if (ft_strlen(line) > (size_t)map_data->w)
			map_data->w = ft_strlen(line);
		if (get_player_pos(line, map_data) == ERROR)
			return (free(line), free(map_data), NULL);
		free(line);
		line = get_next_line(fd_map);
	}
	free(line);
	close(fd_map);
	return (map_data);
}
