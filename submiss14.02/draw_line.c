/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:55:14 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 12:01:27 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_func(t_fpoint *p, t_fdf *data, int z)
{
	data->isometric.prev.x = p->x;
	data->isometric.prev.y = p->y;
	p->x = data->isometric.prev.x * cos(data->window.angle)
		- data->isometric.prev.y * sin(data->window.angle);
	p->y = data->isometric.prev.x * sin(data->window.angle)
		+ data->isometric.prev.y * cos(data->window.angle);
	data->isometric.scaled_z = z * data->window.z_height;
	data->isometric.current_y = p->y;
	p->y = data->isometric.current_y * cos(data->window.pitch)
		- data->isometric.scaled_z * sin(data->window.pitch);
}

void	set_isometric(t_fpoint p, t_fpoint p1, t_fdf *data)
{
	data->isometric.max = get_max(fabs(p1.x - p.x), fabs(p1.y - p.y));
	data->isometric.step.x = (p1.x - p.x) / data->isometric.max;
	data->isometric.step.y = (p1.y - p.y) / data->isometric.max;
	color_pixels(data, p.x, p.y);
}

void	bresenham(t_fpoint p, t_fpoint p1, t_fdf *data)
{
	unsigned int	start_color;
	unsigned int	end_color;

	start_color = data->col_matrix[(int)(p.y)][(int)(p.x)];
	end_color = data->col_matrix[(int)(p1.y)][(int)(p1.x)];
	data->z = (data->matrix[(int)(p.y)][(int)(p.x)]) * (data->window.zoom_z);
	data->z1 = (data->matrix[(int)(p1.y)][(int)(p1.x)]) * (data->window.zoom_z);
	p.x *= data->window.zoom;
	p.y *= data->window.zoom;
	p1.x *= data->window.zoom;
	p1.y *= data->window.zoom;
	isometric_func(&p, data, data->z);
	isometric_func(&p1, data, data->z1);
	p.x += data->window.shift.x;
	p.y += data->window.shift.y;
	p1.x += data->window.shift.x;
	p1.y += data->window.shift.y;
	set_gradient(start_color, end_color, data);
	set_isometric(p, p1, data);
}

void	call_bresenham(t_point p, t_fdf *data)
{
	t_fpoint	fp;
	t_fpoint	fp1;

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
	t_point	p;

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
