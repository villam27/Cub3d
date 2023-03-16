/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/16 13:42:45 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "fcntl.h"

void	check_walls(int **map, int x, int y, t_map_data *map_data)
{
	if (map[y][x] == FLOOR)
		map_data->closed = ERROR;
	if (map[y][x] == NOTHING)
		map[y][x] = CHECKED;
	else
		return ;
	if (x - 1 > 0 && map[y][x - 1] >= FLOOR)
		check_walls(map, x - 1, y, map_data);
	if (x + 1 < map_data->w + 1 && map[y][x + 1] >= FLOOR)
		check_walls(map, x + 1, y, map_data);
	if (y + 1 < map_data->h + 2 && map[y + 1][x] >= FLOOR)
		check_walls(map, x, y + 1, map_data);
	if (y - 1 > 0 && map[y - 1][x] >= FLOOR)
		check_walls(map, x, y - 1, map_data);
}

void	free_map(int **map, int h)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < h)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	is_valid_map(int **map, t_map_data *map_data)
{
	int	**map_cpy;

	map_data->closed = SUCCESS;
	map_cpy = copy_map(map, map_data);
	if (!map_cpy)
		return (ERROR);
	check_walls(map_cpy, 0, 0, map_data);
	if (check_spaces(map_cpy, map_data) == ERROR)
		return (free_map(map_cpy, map_data->h + 2), ERROR);
	free_map(map_cpy, map_data->h + 2);
	if (map_data->closed)
		ilx_err("Map not closed");
	return (map_data->closed);
}

int	**get_map(t_map_data *map_data, int fd_map, char *line)
{
	int		**map;
	int		i;

	i = 0;
	map = malloc(sizeof(int *) * map_data->h);
	if (!map)
		return (free(line), NULL);
	while (line)
	{
		map[i] = set_line(line, map_data->w);
		if (!map[i])
			return (free_map(map, i), free(line), NULL);
		i++;
		free(line);
		line = get_next_line(fd_map);
	}
	if (i != map_data->h)
		return (free_map(map, i), NULL);
	return (map);
}

int	load_maps(t_data *data, char *path)
{
	char		*line;
	int			fd_map;
	int			valid;

	fd_map = open(path, O_RDONLY);
	if (fd_map <= 0)
		return (ERROR);
	data->map_data = get_map_data(path, data);
	if (!data->map_data || data->map_data->player_pos.x == -1)
		return (ilx_err("incorrect map data"), close(fd_map), ERROR);
	line = get_next_line(fd_map);
	while (get_id(line) != 0)
	{
		free(line);
		line = get_next_line(fd_map);
	}
	if (!line)
		return (close(fd_map), ERROR);
	data->map = get_map(data->map_data, fd_map, line);
	if (!data->map)
		return (close(fd_map), ERROR);
	valid = is_valid_map(data->map, data->map_data);
	close(fd_map);
	return (valid);
}
