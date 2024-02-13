/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:55:14 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 21:18:04 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_func(float *x, float *y, t_fdf *data, int z)
{
	data->isometric.prev_x = *x;
	data->isometric.prev_y = *y;
	*x = data->isometric.prev_x * cos(data->window.angle)
		- data->isometric.prev_y * sin(data->window.angle);
	*y = data->isometric.prev_x * sin(data->window.angle)
		+ data->isometric.prev_y * cos(data->window.angle);
	data->isometric.scaled_z = z * data->window.z_height;
	data->isometric.current_y = *y;
	*y = data->isometric.current_y * cos(data->window.pitch)
		- data->isometric.scaled_z * sin(data->window.pitch);
}

void	color_pixels(t_fdf *data, float x, float y)
{
	int	i;

	i = 0;
	while (i <= data->isometric.max)
	{
		interpolate_color(i / data->isometric.max,
			&data->gradient.current_color, data);
		if (x >= 0 && x < data->window.win_x && y >= 0
			&& y < data->window.win_y)
		{
			my_mlx_pixel_put(data, x, y, data->gradient.current_color);
			x += data->isometric.x_step;
			y += data->isometric.y_step;
			i++;
		}
		else
			return ;
	}
}

void set_gradient(unsigned int start_color, unsigned int end_color, t_fdf *data)
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

void set_isometric(t_fpoint p, t_fpoint p1, t_fdf *data)
{
	data->isometric.max = get_max(fabs(p1.x - p.x), fabs(p1.y - p.y));
	data->isometric.x_step = (p1.x - p.x) / data->isometric.max;
	data->isometric.y_step = (p1.y - p.y) / data->isometric.max;
	color_pixels(data, p.x, p.y);
}

void bresenham(t_fpoint p, t_fpoint p1, t_fdf *data)
{
	unsigned int	start_color;
	unsigned int	end_color;

	start_color = data->col_matrix[(int)(p.y)][(int)(p.x)];
	end_color = data->col_matrix[(int)(p1.y)][(int)(p1.x)];
	data->z = data->matrix[(int)(p.y)][(int)(p.x)] * data->window.zoom_z;
	data->z1 = data->matrix[(int)(p1.y)][(int)(p1.x)] * data->window.zoom_z;
	p.x *= data->window.zoom;
	p.y *= data->window.zoom;
	p1.x *= data->window.zoom;
	p1.y *= data->window.zoom;
	isometric_func(&(p.x), &(p.y), data, data->z);
	isometric_func(&(p1.x), &(p1.y), data, data->z1);
	p.x += data->window.shift_x;
	p.y += data->window.shift_y;
	p1.x += data->window.shift_x;
	p1.y += data->window.shift_y;
	set_gradient(start_color, end_color, data);
    set_isometric(p, p1, data);
}

void	make_img(t_fdf *data)
{
	if (data->img == NULL)
	{
		data->img = mlx_new_image(data->mlx_ptr, data->window.win_x,
				data->window.win_y);
		if (!data->img)
			return ;
		data->img_string = mlx_get_data_addr(data->img, &data->bits,
				&data->lsize, &data->endian);
		if (!data->img_string)
			return ;
	}
	else
	{
		ft_bzero(data->img_string, data->window.win_x * data->window.win_y
			* (data->bits / 8));
	}
}

void call_bresenham(t_point p, t_fdf *data)
{
	t_fpoint fp;
	t_fpoint fp1;

	fp.x = p.x;
	fp.y = p.y;
	if (p.x < data->width - 1)
	{
		fp1.x = fp.x + 1;
		fp1.y = fp.y;
		bresenham(fp, fp1, data);
	}
	if (p.y < data->height - 1)
	{
		fp1.x = fp.x;
		fp1.y = fp.y + 1;
		bresenham(fp, fp1, data);
	}
}

void	draw_map(t_fdf *data)
{
	t_point p;
	
	p.y = 0;
	make_img(data);
	calculate_min_max_z(data);
	while (p.y < data->height)
	{
		p.x = 0;
		while (p.x < data->width)
		{
			call_bresenham(p, data);
			p.x++;
		}
		p.y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}
