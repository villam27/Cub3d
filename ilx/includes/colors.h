/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:01:49 by lcrimet           #+#    #+#             */
/*   Updated: 2023/02/15 16:30:58 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include <stdint.h>

typedef struct s_bgra
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}	t_bgra;

typedef union u_color
{
	int32_t		color;
	uint32_t	ucolor;
	t_bgra		tcolor;
}	t_color;

#endif
