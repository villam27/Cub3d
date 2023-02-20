/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:04:14 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/20 10:16:34 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ilx.h"
#include "utils.h"
#include "gui.h"
#include "ilx_texture.h"

typedef struct s_data
{
	t_ilx			*ilx;
	t_gui			*gui;
	uint8_t			clic;
	uint8_t			enable_input;
	t_gui			*current_gui;
	t_ilx_texture	*tex;
}	t_data;

void	*ft_test(void *param)
{
	printf("Hello\n");
	return (param);
}

void	*ft_test2(void *param)
{
	printf("Bonjour\n");
	return (param);
}

void	ilx_change_button_color(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	if (!data->current_gui)
		return ;
	mlx_mouse_get_pos(data->ilx->mlx, data->ilx->window->window, &x, &y);
	while (data->current_gui->buttons[i].label)
	{
		if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].under_cursor_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].under_cursor_label;
			return ;
		}
		else if (data->current_gui->buttons[i].current_color
			== data->current_gui->buttons[i].under_cursor_background)
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].default_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].default_label;
		}
		i++;
	}
}

int	ft_render_next_frame(t_data *data)
{
	ilx_clear_window(data->ilx->window, 0);
	if (!data->clic)
		ilx_change_button_color(data);
	ilx_draw_gui(data->ilx, data->current_gui);
	ilx_draw_texture(data->ilx->window, 10, 10, data->tex);
	ilx_put_img_to_window(data->ilx);
	ilx_draw_gui_text(data->ilx, data->current_gui);
	return (0);
}

int	on_clic(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == RIGHT_CLICK)
	{
		if (!data->current_gui)
			data->current_gui = data->gui;
		else
			data->current_gui = NULL;
	}
	if (key == LEFT_CLICK && data->current_gui)
	{
		data->clic = 1;
		while (data->current_gui->buttons[i].label)
		{
			if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			{
				data->current_gui->buttons[i].current_color
					= data->current_gui->buttons[i].clicked_background;
				data->current_gui->buttons[i].current_label_color
					= data->current_gui->buttons[i].clicked_label;
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	on_release(int key, int x, int y, t_data *data)
{
	int	i;

	i = 0;
	if (key == LEFT_CLICK && data->current_gui)
	{
		data->clic = 0;
		while (data->current_gui->buttons[i].label)
		{
			data->current_gui->buttons[i].current_color
				= data->current_gui->buttons[i].default_background;
			data->current_gui->buttons[i].current_label_color
				= data->current_gui->buttons[i].default_label;
			i++;
		}
		i = 0;
		while (data->current_gui->buttons[i].label)
		{
			if (ilx_mouse_in_button(&data->current_gui->buttons[i], x, y))
			{
				(*data->current_gui->buttons[i].f)(data);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

void	ilx_destroy_window(t_ilx *ilx)
{
	mlx_destroy_image(ilx->mlx, ilx->window->img);
	mlx_destroy_window(ilx->mlx, ilx->window->window);
	free(ilx->window->win_name);
	free(ilx->window);
}

void	*quit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ilx_destroy_texture(data->ilx, data->tex);
	ilx_destroy_window(data->ilx);
	mlx_destroy_display(data->ilx->mlx);
	ilx_destroy_gui(data->gui);
	free(data->ilx->mlx);
	exit (0);
}

int	cross_quit(void *param)
{
	quit(param);
	return (0);
}

int	main(void)
{
	t_ilx			ilx;
	t_data			data;
	t_gui			*test;
	t_button		*button1;
	t_button		*button2;
	t_button		*quit_b;

	ilx = ilx_init();
	ilx.window = ilx_create_window(&ilx, 800, 600, "ILX");
	test = ilx_create_gui();

	data.clic = 0;
	data.enable_input = 1;
	data.current_gui = NULL;

	button1 = ilx_create_button(350, 480, 125, 30);
	ilx_background_button_color(button1, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(button1, 0xffffff, 0, 0);
	ilx_add_button_label(button1, "Test1");

	button2 = ilx_create_button(15, 80, 115, 25);
	ilx_background_button_color(button2, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(button2, 0xffffff, 0, 0);
	ilx_add_button_label(button2, "Bouton");

	quit_b = ilx_create_button(370, 270, 50, 20);
	ilx_background_button_color(quit_b, 0xff0000, 0x00ff00, 0x0000ff);
	ilx_label_button_color(quit_b, 0xffffff, 0, 0);
	ilx_add_button_label(quit_b, "Quit");

	ilx_add_button(test, button1, &ft_test2);
	ilx_add_button(test, button2, &ft_test);
	ilx_add_button(test, quit_b, &quit);

	data.ilx = &ilx;
	data.gui = test;
	data.tex = ilx_create_texture(&ilx, "assets/rocket.xpm");
	if (!data.tex)
		return(printf("cant load image\n"), quit(&data), 0);
	mlx_loop_hook(ilx.mlx, ft_render_next_frame, &data);
	mlx_hook(ilx.window->window, ON_DESTROY, 0, cross_quit, &data);
	mlx_hook(ilx.window->window, ON_MOUSEDOWN, 1L << 2, on_clic, &data);
	mlx_hook(ilx.window->window, ON_MOUSEUP, 1L << 3, on_release, &data);
	mlx_loop(ilx.mlx);

	return (0);
}
