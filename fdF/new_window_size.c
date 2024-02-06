#include "fdf.h"

int	check_window_size(int keycode, fdf *data)
{
	if ((keycode == 20 && data->window.win_y <= 500) || (keycode == 18
			&& data->window.win_x <= 500))
		return (1);
	if ((keycode == 21 && data->window.win_y > 1000) || (keycode == 19
			&& data->window.win_x > 2000))
		return (1);
	return (0);
}

void	new_size(int keycode, fdf *data)
{
	if (check_window_size(keycode, data))
		return ;
	if (keycode == 18)
		data->window.win_x -= 100;
	if (keycode == 19)
		data->window.win_x += 100;
	if (keycode == 20)
		data->window.win_y -= 100;
	if (keycode == 21)
		data->window.win_y += 100;
}

void	change_window(int keycode, fdf *data)
{
	new_size(keycode, data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.win_x,
			data->window.win_y, "FDF");
	mlx_hook(data->win_ptr, 2, 1, key_hoo, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	draw_map(data);
}