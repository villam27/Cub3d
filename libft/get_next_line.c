/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:31:33 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/06 14:52:51 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_newline(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i] && src[i] != '\n')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = src[i];
	j++;
	dest[j] = 0;
	return (dest);
}

char	*ft_new_str(char *str, char *buffer, char *str_cp, int i)
{
	str_cp = malloc(sizeof(char) * (ft_strlen(str) + i + 2));
	if (!str_cp)
		return (0);
	str_cp = ft_strcpy(str_cp, str);
	str_cp = ft_strcat_newline(str_cp, buffer);
	free(str);
	return (str_cp);
}

char	*ft_cut_buffer(char *str, char *buffer)
{
	int		i;
	char	*str_cp;

	i = 0;
	str_cp = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			if (!str)
			{
				str_cp = malloc(sizeof(char) * (i + 2));
				if (!str_cp)
					return (0);
				str_cp[0] = 0;
				str_cp = ft_strcat_newline(str_cp, buffer);
			}
			else
				str_cp = ft_new_str(str, buffer, str_cp, i);
			ft_init_buffer(buffer, i + 1);
			return (str_cp);
		}
		i++;
	}
	return (0);
}

char	*ft_add_buffer(char *str, char *buffer)
{
	char	*str_cp;

	if (!buffer[0])
		return (0);
	if (!str)
	{
		str_cp = malloc(sizeof(char) * (ft_strlen(buffer) + 2));
		str_cp = ft_strcpy(str_cp, buffer);
	}
	else
	{
		str_cp = malloc(sizeof(char) * (ft_strlen(str)
					+ ft_strlen(buffer) + 2));
		str_cp = ft_strcpy(str_cp, str);
		str_cp = ft_strcat(str_cp, buffer);
		free(str);
	}
	return (str_cp);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	int			read_char;
	char		*current_line;

	if (BUFFER_SIZE <= 0 || read(fd, buffer, 0) == -1)
		return (0);
	read_char = 1;
	current_line = 0;
	while (read_char > 0)
	{
		if (ft_is_newline(buffer))
			return (ft_cut_buffer(current_line, buffer));
		current_line = ft_add_buffer(current_line, buffer);
		read_char = read(fd, buffer, BUFFER_SIZE);
		buffer[read_char] = 0;
	}
	return (current_line);
}
