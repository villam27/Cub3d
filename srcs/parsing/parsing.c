/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/03 16:12:48 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "fcntl.h"

int	get_id(char *line)
{
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

void	set_id(int id, t_data *map_data, char *line)
{
	int	len;

	len = ft_strlen(line);
	line[len - 1] = 0;
	if (id == EMPTY_LINE)
		return ;
	if (id == NO)
		map_data->north_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == SO)
		map_data->south_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == WE)
		map_data->west_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == EA)
		map_data->east_texture = ilx_create_texture(map_data->ilx, line + 3);
	ft_printf("%s\n", line + 3);
}

int	check_data_integrity(t_data *data)
{
	if (data->north_texture == NULL || data->south_texture == NULL || data->west_texture == NULL || data->east_texture == NULL)
		return (1);
	return (0);
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

t_map_data	*get_map_data(char *path, t_data *data)
{
	int			fd_map;
	t_map_data	*map_data;
	char		*line;
	int			id;

	map_data = init_map_data();
	if (!map_data)
		return (NULL);
	fd_map = open(path, O_RDONLY);
	line = get_next_line(fd_map);
	id = EMPTY_LINE;
	while (id != NO_ID)
	{
		id = get_id(line);
		if (id)
		{
			set_id(id, data, line);
			free(line);
			line = get_next_line(fd_map);
		}
	}
	if (check_data_integrity(data))
		return (free(line), NULL); //free all
	while (line)
	{
		map_data->h += 1;
		if (ft_strlen(line) > (size_t)map_data->w)
			map_data->w = ft_strlen(line);
		free(line);
		line = get_next_line(fd_map);
	}
	free(line);
	close(fd_map);
	return (map_data);
}

int *set_line(char *line, int len)
{
	int	*line_data;
	int	i;
	int l_len;

	i = 0;
	l_len = ft_strlen(line);
	line_data = malloc(sizeof(int) * len);
	if (!line_data)
		return (NULL);
	(void)line;
	while (i < len)
	{
		line_data[i] = NOTHING;
		if (l_len > i && line[i] == '1')
			line_data[i] = WALL;
		if (l_len > i && line[i] == '0')
			line_data[i] = FLOOR;
		i++;
	}
	return (line_data);
}

int	**copy_map(int **map, t_map_data *map_data)
{
	int	**map_cpy;
	int	i;
	int	j;

	i = 0;
	map_cpy = malloc(sizeof(int *) * (map_data->h + 2));
	if (!map_cpy)
		return (NULL);
	while (i < map_data->h + 2)
	{
		map_cpy[i] = malloc(sizeof(int) * (map_data->w + 1));
		if (!map_cpy[i])
			return (NULL);
		j = 0;
		while (j < map_data->w + 1)
		{
			map_cpy[i][j] = NOTHING;
			j++;
		}
		i++;
	}
	i = 1;
	while (i < map_data->h + 1)
	{
		j = 1;
		while (j < map_data->w)
		{
			map_cpy[i][j] = map[i - 1][j - 1];
			j++;
		}
		i++;
	}
	print_map(map_cpy, MAP_WIDTH + 1, MAP_HEIGHT + 2);
	return (map_cpy);
}

void	check_walls(int **map, int x, int y, int *closed)
{
	if (map[y][x] == FLOOR)
		*closed = 0;
	if (map[y][x] == NOTHING)
		map[y][x] = BT_FILL;
	else
		return ;
	if (x - 1 > 0 && map[y][x - 1] >= FLOOR)
		check_walls(map, x - 1, y, closed);
	if (x + 1 < MAP_WIDTH + 1 && map[y][x + 1] >= FLOOR)
		check_walls(map, x + 1, y, closed);
	if (y + 1 < MAP_HEIGHT + 2 && map[y + 1][x] >= FLOOR)
		check_walls(map, x, y + 1, closed);
	if (y - 1 > 0 && map[y - 1][x] >= FLOOR)
		check_walls(map, x, y - 1, closed);
}

void	free_map(int **map, int h)
{
	int	i;

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
	int closed;

	closed = 1;
	map_cpy = copy_map(map, map_data);
	check_walls(map_cpy, 0, 0, &closed);
	print_map(map_cpy, MAP_WIDTH + 1, MAP_HEIGHT + 2);
	free_map(map_cpy, map_data->h + 2);
	return (closed);
}

int	load_maps(t_data *data, char *path)
{
	t_map_data	*map_data;
	char		*line;
	int			fd_map;
	int			i;
	int			valid;

	i = 0;
	map_data = get_map_data(path, data);
	fd_map = open(path, O_RDONLY);
	line = get_next_line(fd_map);
	while (get_id(line) != 0)
	{
		free(line);
		line = get_next_line(fd_map);
	}
	data->map = malloc(sizeof(int *) * map_data->h);
	if (!data->map)
		return (free(line), 0);
	while (line)
	{
		data->map[i] = set_line(line, map_data->w);
		i++;
		free(line);
		line = get_next_line(fd_map);
	}
	valid = is_valid_map(data->map, map_data);
	free(line);
	close(fd_map);
	free(map_data);
	return (valid);
}
