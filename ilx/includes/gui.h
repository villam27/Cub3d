/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:45:57 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/07 12:27:57 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <stdlib.h>
# include "colors.h"
# include "libft.h"
# include "ilx_shapes.h"
# include "ilx.h"
# include "ilx_keycodes.h"
# include "ilx_texture.h"

typedef struct s_button
{
	t_rectangle	rect;
	char		*label;
	uint32_t	default_background;
	uint32_t	default_label;
	uint32_t	clicked_background;
	uint32_t	clicked_label;
	uint32_t	under_cursor_background;
	uint32_t	under_cursor_label;
	uint32_t	current_color;
	uint32_t	current_label_color;
	void		*(*f)(void *);
}	t_button;

typedef struct s_textured_buton
{
	t_ilx_texture	*text_ptr;
	t_point			*pos;
	t_rectangle		default_rect;
	t_rectangle		default_tex_pos;
	t_rectangle		under_tex_pos;
	t_rectangle		clicked_tex_pos;
	size_t			under_steps;
	uint32_t		speed;
	void			*(*f)(void *);
}	t_textured_button;

typedef struct s_gui
{
	t_button		*buttons;
}	t_gui;

/* Button creation need the 4 next function in this order to be correctly
   initialize (thanks norminette). */

t_button	*ilx_create_button(int x, int y, int width, int height);
void		ilx_background_button_color(t_button *button, uint32_t default_c,
				uint32_t under_cursor, uint32_t clicked);
void		ilx_label_button_color(t_button *button, uint32_t default_c,
				uint32_t under_cursor, uint32_t clicked);
void		ilx_add_button_label(t_button *button, char *label);

/* Add a button to a gui element. You can have mutliple gui, one for each menu.
   This function take a function pointer on the function called by the
   button. */

int			ilx_add_button(t_gui *gui, t_button *add_button,
				void *(*f)(void *));

/* Check if the x y coordinates are in the button */

uint8_t		ilx_mouse_in_button(t_button *button, int x, int y);

/* Gui must be create as a pointer and should not be malloc before
   ilx_create_gui. You don't have to free gui after ilx_destroy_gui. */

t_gui		*ilx_create_gui(void);
void		ilx_destroy_gui(t_gui *gui);

/* Call ilx_draw_gui_text after the ilx_push_image_to_window
   in order to see the text.*/

void		ilx_draw_gui(t_ilx *ilx, t_gui *gui);
void		ilx_draw_gui_text(t_ilx *ilx, t_gui *gui);

/*
	TEXTURED	BUTTONS
*/
t_textured_button	*ilx_create_tex_button(int x, int y, char *label, t_ilx_texture *tex_ptr);
void				ilx_set_tex_button_rects(t_textured_button *button, t_rectangle def, t_rectangle under, t_rectangle click);
void				ilx_set_tex_button_datas(t_textured_button *button, size_t step, uint32_t speed);

int					ilx_add_tex_button(t_gui *gui, t_textured_button *add_button, void *(*f)(void *));

#endif