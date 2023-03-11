/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/11 15:13:46 by alboudje         ###   ########.fr       */
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

int		set_texture(t_ilx_texture **texture, t_data *data, char *line)
{
	if (*texture == NULL)
		*texture = ilx_create_texture(data->ilx, line + 3);
	else
		return (0);
	return (1);
}

int	set_id(int id, t_data *map_data, char *line)
{
	int	len;

	len = ft_strlen(line);
	line[len - 1] = 0;
	if (id == EMPTY_LINE)
		return (1);
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
	return (1);
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

	fd_map = open(path, O_RDONLY);
	if (fd_map <= 0)
		return (NULL);
	map_data = init_map_data();
	if (!map_data)
		return (NULL);
	line = get_next_line(fd_map);
	id = EMPTY_LINE;
	while (id != NO_ID)
	{
		id = get_id(line);
		if (id)
		{
			if (!set_id(id, data, line))
				ft_printf("texture already exist\n");
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
	//print_map(map_cpy, MAP_WIDTH + 1, MAP_HEIGHT + 2);
	return (map_cpy);
}

void	check_walls(int **map, int x, int y, t_map_data *map_data)
{
	if (map[y][x] == FLOOR)
		map_data->closed = ERROR;
	if (map[y][x] == NOTHING)
		map[y][x] = BT_FILL;
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
	check_walls(map_cpy, 0, 0, map_data);
	print_map(map_cpy, map_data->w + 1, map_data->h + 2);
	free_map(map_cpy, map_data->h + 2);
	ft_printf(">>>> %d\n", map_data->closed);
	return (map_data->closed);
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
	if (!map_data)
		return (ERROR);
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
