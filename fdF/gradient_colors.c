#include "fdf.h"

void	interpolate_color(float step_ratio, int *current_color, fdf *data)
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

int	get_min_z(fdf *data)
{
	int	min_z;
	int	x;
	int	y;

	min_z = INT_MAX;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->matrix[y][x] < min_z)
				min_z = data->matrix[y][x];
			x++;
		}
		y++;
	}
	return (min_z);
}

int	get_max_z(fdf *data)
{
	int	max_z;
	int	x;
	int	y;

	max_z = INT_MIN;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->matrix[y][x] > max_z)
				max_z = data->matrix[y][x];
			x++;
		}
		y++;
	}
	return (max_z);
}

int	determine_color_based_on_z(int z, fdf *data)
{
	float adjust_z;

	data->gradient.min_z = get_min_z(data);
	data->gradient.max_z = get_max_z(data);
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