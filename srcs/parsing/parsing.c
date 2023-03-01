/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:17 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/01 16:36:52 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "fcntl.h"

int	get_id(char *line)
{
	(void)line;
	return (0);
}

void	set_id(int id, t_map_data *map_data, char *line)
{
	(void)id;
	(void)map_data;
	(void)line;
}

int	check_data_integrity(t_map_data *map_data)
{
	(void)map_data;
	return (0);
}

t_map_data	*get_map_data(char *path)
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
			set_id(id, map_data, line);
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

int	load_map(t_data *data, char *path)
{
	t_map_data	*map_data;

	map_data = get_map_data(path);
}
