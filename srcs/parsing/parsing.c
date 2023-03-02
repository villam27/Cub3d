/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/02 11:58:34 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "fcntl.h"

int	get_id(char *line)
{
	if (line[0] == '\n')
		return (-1);
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
	int	len;

	len = ft_strlen(line);
	line[len - 1] = 0;
	if (id < 0)
		return ;
	if (id == 1)
		map_data->north_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == 2)
		map_data->south_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == 3)
		map_data->west_texture = ilx_create_texture(map_data->ilx, line + 3);
	if (id == 4)
		map_data->east_texture = ilx_create_texture(map_data->ilx, line + 3);
	ft_printf("%s\n", line + 3);
}

int	check_data_integrity(t_map_data *map_data)
{
	(void)map_data;
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
	if (check_data_integrity(map_data))
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
	//memset(line_data, 0, len);
	(void)line;
	while (i < len)
	{
		line_data[i] = 0;
		if (l_len > i && line[i] == '1')
			line_data[i] = 1;
		i++;
	}
	return (line_data);
}

int	load_maps(t_data *data, char *path)
{
	t_map_data	*map_data;
	char		*line;
	int			fd_map;
	int			i;

	i = 0;
	map_data = get_map_data(path, data);
	fd_map = open(path, O_RDONLY);
	line = get_next_line(fd_map);
	while (get_id(line) != 0)
	{
		free(line);
		line = get_next_line(fd_map);
	}
	ft_printf(">> w:%d h:%d\n", map_data->h, map_data->w);
	data->map = malloc(sizeof(int *) * 14);
	if (!data->map)
		return (free(line), 0);
	while (line)
	{
		data->map[i] = set_line(line, 34);
		i++;
		free(line);
		line = get_next_line(fd_map);
	}
	free(line);
	close(fd_map);
	free(map_data);
	return (1);
}
