/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:00:23 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/21 14:46:00 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"

void	ilx_put_img_to_window(t_ilx *ilx)
{
	mlx_put_image_to_window(ilx->mlx, ilx->window->window,
		ilx->window->img, 0, 0);
}

t_window	*ilx_create_window(t_ilx *ilx, int x, int y, char *win_name)
{
	void	*mlx_win;

	mlx_win = mlx_new_window(ilx->mlx, x, y, win_name);
	ilx->window = ft_new_window(mlx_win, win_name);
	if (!ilx->window)
		return (NULL);
	ilx->window->img = mlx_new_image(ilx->mlx, x, y);
	ilx->window->win_width = x;
	ilx->window->win_height = y;
	ilx->window->win_name = ft_strdup(win_name);
	ilx->window->addr = mlx_get_data_addr(ilx->window->img,
			&ilx->window->bits_per_pixel, &ilx->window->line_length,
			&ilx->window->endian);
	ilx->window->renderer = (unsigned int *)ilx->window->addr;
	return (ilx->window);
}

void	ilx_clear_window(t_window *window, uint32_t color)
{
	int	i;
	int	max;
	
	i = 0;
	max = window->win_height * window->win_width;
	while (i < max)
	{
		window->renderer[i] = color;
		i++;
	}
}


t_window	*ft_new_window(void *win, char *win_name)
{
	t_window	*new;

	new = malloc(sizeof(t_window));
	if (!new)
		return (NULL);
	new->window = win;
	new->win_name = win_name;
	return (new);
}

t_ilx	ilx_init(void)
{
	t_ilx	ilx;

	ilx.mlx = mlx_init();
	ilx.window = NULL;
	return (ilx);
}
