/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:36:50 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/16 10:37:15 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "errno.h"

int	get_player_pos(char *line, t_map_data *map_data)
{
	int	i;

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
		|| data->west_texture == NULL || data->east_texture == NULL)
		return (ERROR);
	if (data->ceiling_color == 0 || data->floor_color == 0)
		return (ERROR);
	return (SUCCESS);
}

/*int check_closed(int **map, int x, int y, int len)
{
	if ((i > 0 && line[i - 1] == '0') || (i < len && line[i + 1] == 0))
		return (free(line_data), ERROR);
	return (SUCCESS);
}*/

int	*set_line(char *line, int len, int **map, int y)
{
	int	*line_data;
	int	i;
	int	l_len;
	(void)map;
	(void)y;

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
		else if (l_len > i && (line[i] == '0' || ft_strchr("NSEW", line[i])))
			line_data[i] = FLOOR;
		/*else if (l_len > i && line[i] == ' ')
		{
		}*/
		else if (l_len - 1 > i)
			return (free(line_data), NULL);
		i++;
	}
	return (line_data);
}

void	copy_map_data(int **map, int ***map_cpy, t_map_data *map_data)
{
	int	i;
	int	j;

	i = 1;
	while (i < map_data->h + 1)
	{
		j = 1;
		while (j < map_data->w)
		{
			(*map_cpy)[i][j] = map[i - 1][j - 1];
			j++;
		}
		i++;
	}
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
	copy_map_data(map, &map_cpy, map_data);
	return (map_cpy);
}
