/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:54:28 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 12:00:24 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	interpolate_color(float step_ratio, int *current_color, t_fdf *data)
{
	data->rgb.start_r = (data->gradient.start_color >> 16) & 0xFF;
	data->rgb.start_g = (data->gradient.start_color >> 8) & 0xFF;
	data->rgb.start_b = data->gradient.start_color & 0xFF;
	data->rgb.end_r = (data->gradient.end_color >> 16) & 0xFF;
	data->rgb.end_g = (data->gradient.end_color >> 8) & 0xFF;
	data->rgb.end_b = data->gradient.end_color & 0xFF;
	data->rgb.r = (int)(data->rgb.start_r + (data->rgb.end_r
				- data->rgb.start_r) * step_ratio);
	data->rgb.g = (int)(data->rgb.start_g + (data->rgb.end_g
				- data->rgb.start_g) * step_ratio);
	data->rgb.b = (int)(data->rgb.start_b + (data->rgb.end_b
				- data->rgb.start_b) * step_ratio);
	*current_color = ((data->rgb.r << 16) | (data->rgb.g << 8) | data->rgb.b);
}

void	calculate_min_max_z(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	data->gradient.min_z = INT_MAX;
	data->gradient.max_z = INT_MIN;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->matrix[y][x] < data->gradient.min_z)
				data->gradient.min_z = data->matrix[y][x];
			if (data->matrix[y][x] > data->gradient.max_z)
				data->gradient.max_z = data->matrix[y][x];
			x++;
		}
		y++;
	}
}

int	determine_color_based_on_z(int z, t_fdf *data)
{
	float	adjust_z;

	if (data->gradient.max_z == data->gradient.min_z)
		return (data->gradient.min_color);
	adjust_z = (float)(z - data->gradient.min_z) / (data->gradient.max_z
			- data->gradient.min_z);
	data->rgb.min_r = (data->gradient.min_color >> 16) & 0xFF;
	data->rgb.min_g = (data->gradient.min_color >> 8) & 0xFF;
	data->rgb.min_b = data->gradient.min_color & 0xFF;
	data->rgb.max_r = (data->gradient.max_color >> 16) & 0xFF;
	data->rgb.max_g = (data->gradient.max_color >> 8) & 0xFF;
	data->rgb.max_b = data->gradient.max_color & 0xFF;
	data->rgb.r = data->rgb.min_r + (int)(adjust_z * (data->rgb.max_r
				- data->rgb.min_r));
	data->rgb.g = data->rgb.min_g + (int)(adjust_z * (data->rgb.max_g
				- data->rgb.min_g));
	data->rgb.b = data->rgb.min_b + (int)(adjust_z * (data->rgb.max_b
				- data->rgb.min_b));
	return ((data->rgb.r << 16) | (data->rgb.g << 8) | data->rgb.b);
}

void	color_pixels(t_fdf *data, float x, float y)
{
	int	i;

	i = 0;
	while (i <= data->isometric.max)
	{
		interpolate_color(i / data->isometric.max,
			&data->gradient.current_color, data);
		if (x >= 0 && x < data->window.win.x && y >= 0
			&& y < data->window.win.y)
		{
			my_mlx_pixel_put(data, x, y, data->gradient.current_color);
			x += data->isometric.step.x;
			y += data->isometric.step.y;
			i++;
		}
		else
			return ;
	}
}

void	set_gradient(unsigned int start_color, unsigned int end_color,
		t_fdf *data)
{
	if (start_color == 0)
		data->gradient.start_color = determine_color_based_on_z(data->z, data);
	else
		data->gradient.start_color = start_color;
	if (end_color == 0)
		data->gradient.end_color = determine_color_based_on_z(data->z1, data);
	else
		data->gradient.end_color = end_color;
}
