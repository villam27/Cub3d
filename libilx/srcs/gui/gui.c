/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:46:23 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/17 15:58:23 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <stdio.h>

void	ilx_draw_gui(t_ilx	*ilx, t_gui *gui)
{
	int	i;

	i = 0;
	if (!gui)
		return ;
	while (gui->buttons[i].label)
	{
		ilx_draw_fill_rect(ilx->window, &gui->buttons[i].rect,
			gui->buttons[i].current_color);
		i++;
	}
}

void	ilx_draw_gui_text(t_ilx	*ilx, t_gui *gui)
{
	int	i;

	i = 0;
	if (!gui)
		return ;
	while (gui->buttons[i].label)
	{
		mlx_string_put(ilx->mlx, ilx->window->window, gui->buttons[i].rect.x
			+ gui->buttons[i].rect.width / 2 - ft_strlen(gui->buttons[i].label)
			* 3, gui->buttons[i].rect.y + gui->buttons[i].rect.height / 2 + 4,
			gui->buttons[i].current_label_color, gui->buttons[i].label);
		i++;
	}
}

t_gui	*ilx_create_gui(void)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	gui->buttons = NULL;
	return (gui);
}

void	ilx_destroy_gui(t_gui *gui)
{
	int	i;

	i = 0;
	while (gui->buttons[i].label)
	{
		free(gui->buttons[i].label);
		i++;
	}
	free(gui->buttons);
	free(gui);
}
