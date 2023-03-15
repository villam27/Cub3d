/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:36:50 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/15 12:08:56 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_player_pos(char *line, t_map_data *map_data)
{
	int			i;

	i = 0;
	if (!line)
		return (ERROR);
	while (line[i])
	{
		if (ft_strchr("NSEW", line[i]))
		{
			if (map_data->player_pos.x > 0)
				return (ERROR);
			map_data->player_pos.x = i;
			map_data->player_pos.y = map_data->h - 1;
			map_data->direction = line[i];
		}
		i++;
	}
	return (SUCCESS);
}

int	check_data_integrity(t_data *data)
{
	if (data->north_texture == NULL || data->south_texture == NULL
		|| data->west_texture == NULL || data->east_texture == NULL
		|| data->floor_texture == NULL || data->ceiling_texture == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	*set_line(char *line, int len)
{
	int	*line_data;
	int	i;
	int	l_len;

	i = 0;
	l_len = ft_strlen(line);
	line_data = malloc(sizeof(int) * len);
	if (!line_data || !line)
		return (free(line_data), NULL);
	while (i < len)
	{
		line_data[i] = NOTHING;
		if (l_len > i && line[i] == '1')
			line_data[i] = WALL;
		if (l_len > i && (line[i] == '0' || ft_strchr("NSEW", line[i])))
			line_data[i] = FLOOR;
		else
			return (free(line_data), NULL);
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
			return (free_map(map_cpy, i), NULL);
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
	return (map_cpy);
}
