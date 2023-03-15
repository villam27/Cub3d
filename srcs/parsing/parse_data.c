/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:34:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/15 21:20:46 by alboudje         ###   ########.fr       */
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
	if (!ft_strncmp(line, "WE", 2))
		return (WE);
	if (!ft_strncmp(line, "EA", 2))
		return (EA);
	if (!ft_strncmp(line, "F ", 2))
		return (FL);
	if (!ft_strncmp(line, "C ", 2))
		return (CE);
	if (!ft_strncmp(line, "FT", 2))
		return (FT);
	if (!ft_strncmp(line, "CT", 2))
		return (CT);
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

/*
	TODO: fix line = NULL;
*/

int	get_data_utils(t_data *data, char *line, int fd_map, t_map_data *map_data)
{
	if (check_data_integrity(data) == ERROR)
		return (free(line), free(map_data), ERROR);
	while (line)
	{
		map_data->h += 1;
		if (ft_strlen(line) > (size_t)map_data->w)
			map_data->w = ft_strlen(line);
		if (get_player_pos(line, map_data) == ERROR)
			return (free(line), free(map_data), ERROR);
		free(line);
		line = get_next_line(fd_map);
	}
	free(line);
	close(fd_map);
	return (SUCCESS);
}

int	get_data_init(char *path, int *fd_map, t_map_data **map_data)
{
	*fd_map = open(path, O_RDONLY);
	if (*fd_map <= 0)
		return (ERROR);
	*map_data = init_map_data();
	if (!(*map_data))
		return (ERROR);
	(*map_data)->player_pos.x = -1;
	return (SUCCESS);
}

t_map_data	*get_map_data(char *path, t_data *data)
{
	int			fd_map;
	t_map_data	*map_data;
	char		*line;
	int			id;

	if (get_data_init(path, &fd_map, &map_data) == ERROR)
		return (NULL);
	line = get_next_line(fd_map);
	id = EMPTY_LINE;
	while (id != NO_ID)
	{
		id = get_id(line);
		if (id)
		{
			if (set_id(id, data, line))
				return (free(line), free(map_data), NULL);
			free(line);
			line = get_next_line(fd_map);
		}
	}
	if (get_data_utils(data, line, fd_map, map_data) == ERROR)
		return (NULL);
	return (map_data);
}
