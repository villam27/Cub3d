/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:47:27 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/24 12:54:03 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_BINDING_H
# define KEY_BINDING_H

# include "data.h"
# include "cub3D.h"

int	on_clic(int key, int x, int y, t_data *data);
int	on_release(int key, int x, int y, t_data *data);
int	ft_press_key(int keycode, t_data *data);
int	ft_up_key(int keycode, t_data *data);

#endif