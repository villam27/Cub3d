/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:33:01 by alboudje          #+#    #+#             */
/*   Updated: 2023/03/15 20:33:59 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "errno.h"

int	set_color(uint32_t *color, char *line)
{
	char	**sp;
	int		i;
	int		r;
	int		g;
	int		b;

	if (*color != 0)
		return (ERROR);
	i = 0;
	sp = ft_split(line + 2, ",");
	if (!sp)
		return (ERROR);
	while (sp[i])
		i++;
	if (i != 3)
		return (ft_freeall(sp), ERROR);
	r = ft_atoi(sp[0]);
	g = ft_atoi(sp[1]);
	b = ft_atoi(sp[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255)
		|| (b < 0 || b > 255) || errno == 42)
		return (ft_freeall(sp), ERROR);
	*color = ilx_create_trgb(255, r, g, b);
	return (ft_freeall(sp), SUCCESS);
}

int	set_id(int id, t_data *map_data, char *line)
{
	int	len;

	len = ft_strlen(line);
	line[len - 1] = 0;
	if (id == EMPTY_LINE)
		return (SUCCESS);
	if (id == NO)
		return (set_texture(&map_data->north_texture, map_data, line));
	if (id == SO)
		return (set_texture(&map_data->south_texture, map_data, line));
	if (id == WE)
		return (set_texture(&map_data->west_texture, map_data, line));
	if (id == EA)
		return (set_texture(&map_data->east_texture, map_data, line));
	if (id == FT)
		return (set_texture(&map_data->floor_texture, map_data, line));
	if (id == CT)
		return (set_texture(&map_data->ceiling_texture, map_data, line));
	if (id == FL)
		return (set_color(&map_data->floor_color, line));
	if (id == CE)
		return (set_color(&map_data->ceiling_color, line));
	return (ERROR);
}

int	set_texture(t_ilx_texture **texture, t_data *data, char *line)
{
	if (*texture == NULL)
		*texture = ilx_create_texture(data->ilx, line + 3);
	else
		return (ERROR);
	return (SUCCESS);
}
