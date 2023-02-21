/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:48:25 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/21 15:44:07 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILX_H
# define ILX_H

# include "mlx.h"
# include "ft_window.h"
# include "ilx_shapes.h"
# include "colors.h"

# define FILL 0
# define EMPTY 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_ilx
{
	t_window	*window;
	void		*mlx;
}	t_ilx;

#endif