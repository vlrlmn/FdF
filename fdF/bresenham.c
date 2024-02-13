/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:49:01 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 18:54:26 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	width_bresenham(int x, int y, t_fdf *data)
{
	int	x1;
	int	y1;
	unsigned int	start_color;
	unsigned int	end_color;

	x1 = x + 1;
	y1 = y;
	start_color = data->col_matrix[(int)y][(int)x];
	end_color = data->col_matrix[(int)y1][(int)x1];
	data->z = data->matrix[(int)y][(int)x] * data->window.zoom_z;
	data->z1 = data->matrix[(int)y1][(int)x1] * data->window.zoom_z;
	x *= data->window.zoom;
	y *= data->window.zoom;
	x1 *= data->window.zoom;
	y1 *= data->window.zoom;
	isometric_func(&x, &y, data, data->z);
	isometric_func(&x1, &y1, data, data->z1);
	x += data->window.shift_x;
	y += data->window.shift_y;
	x1 += data->window.shift_x;
	y1 += data->window.shift_y;
	if (start_color == 0)
		data->gradient.start_color = determine_color_based_on_z(data->z, data);
	else
		data->gradient.start_color = start_color;
	if (end_color == 0)
		data->gradient.end_color = determine_color_based_on_z(data->z1, data);
	else
		data->gradient.end_color = end_color;
	data->isometric.max = get_max(fabs(x1 - x), fabs(y1 - y));
	data->isometric.x_step = (x1 - x) / data->isometric.max;
	data->isometric.y_step = (y1 - y) / data->isometric.max;
	color_pixels(data, x, y);
}

void	height_bresenham(int x, int y, t_fdf *data)
{
	int	x1;
	int	y1;
	unsigned int	start_color;
	unsigned int	end_color;

	x1 = x;
	y1 = y + 1;
	start_color = data->col_matrix[(int)y][(int)x];
	end_color = data->col_matrix[(int)y1][(int)x1];
	data->z = data->matrix[(int)y][(int)x] * data->window.zoom_z;
	data->z1 = data->matrix[(int)y1][(int)x1] * data->window.zoom_z;
	x *= data->window.zoom;
	y *= data->window.zoom;
	x1 *= data->window.zoom;
	y1 *= data->window.zoom;
	isometric_func(&x, &y, data, data->z);
	isometric_func(&x1, &y1, data, data->z1);
	x += data->window.shift_x;
	y += data->window.shift_y;
	x1 += data->window.shift_x;
	y1 += data->window.shift_y;
	if (start_color == 0)
		data->gradient.start_color = determine_color_based_on_z(data->z, data);
	else
		data->gradient.start_color = start_color;
	if (end_color == 0)
		data->gradient.end_color = determine_color_based_on_z(data->z1, data);
	else
		data->gradient.end_color = end_color;
	data->isometric.max = get_max(fabs(x1 - x), fabs(y1 - y));
	data->isometric.x_step = (x1 - x) / data->isometric.max;
	data->isometric.y_step = (y1 - y) / data->isometric.max;
	color_pixels(data, x, y);
}