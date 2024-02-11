#include "fdf.h"

float	get_max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	isometric_func(float *x, float *y, fdf *data, int z)
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

void	my_mlx_pixel_put(fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < data->window.win_x && y >= 0 && y < data->window.win_y)
	{
		dst = data->img_string + (y * data->lsize + x * (data->bits / 8));
		*(unsigned int*)dst = color;
	}
}

void	color_pixels(fdf *data, float x, float y)
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
			my_mlx_pixel_put(data, x, y,
				data->gradient.current_color);
			x += data->isometric.x_step;
			y += data->isometric.y_step;
			i++;
		}
		else
			return ;
	}
}

void	bresenham(float x, float y, float x1, float y1, fdf *data)
{
	unsigned int start_color = data->color_matrix[(int)y][(int)x];
    unsigned int end_color = data->color_matrix[(int)y1][(int)x1];

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

void	draw_map(fdf *data)
{
	int	x;
	int	y;

	y = 0;
	if (data->img == NULL) 
	{
		data->img = mlx_new_image(data->mlx_ptr, data->window.win_x, data->window.win_y);
		if (!data->img)
			return;
		data->img_string = mlx_get_data_addr(data->img, &data->bits, &data->lsize, &data->endian);
		if (!data->img_string)
			return;
	}
	else
	{
		ft_bzero(data->img_string, data->window.win_x * data->window.win_y * (data->bits / 8));
	}
	calculate_min_max_z(data);
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresenham(x, y, x + 1, y, data);
			if (y < data->height - 1)
				bresenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}
