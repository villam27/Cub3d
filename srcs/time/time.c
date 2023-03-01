/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:35:23 by lcrimet           #+#    #+#             */
/*   Updated: 2023/03/01 11:50:49 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	get_frame_time(long start_time)
{
	long			current_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000 + time.tv_usec / 1000) - start_time;
	return (current_time);
}

long	get_start_time(void)
{
	struct timeval	time;
	long			start_time;

	gettimeofday(&time, NULL);
	start_time = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (start_time);
}
