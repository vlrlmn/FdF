/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:52:47 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 21:45:09 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_key(int keycode)
{
	return ((keycode >= 123 && keycode <= 126) || keycode == 0 || keycode == 1
		|| (keycode >= 6 && keycode <= 9) || keycode == 45 || keycode == 11
		|| keycode == 53 || (keycode >= 18 && keycode <= 21));
}

void	exec_key(int keycode, t_fdf *data)
{
	ft_printf(BOLD "Pressed button: %d!\n", keycode, RESET);
	if (keycode == 126)
		data->window.shift.y -= 10;
	if (keycode == 125)
		data->window.shift.y += 10;
	if (keycode == 124)
		data->window.shift.x += 10;
	if (keycode == 123)
		data->window.shift.x -= 10;
	if (keycode == 0)
		data->window.angle += 0.05;
	if (keycode == 1)
		data->window.angle -= 0.05;
	if (keycode == 6)
		data->window.zoom += 3;
	if (keycode == 7)
		data->window.zoom -= 3;
	if (keycode == 8)
		data->window.zoom_z = fmin(data->window.zoom_z + 0.5, MAX_ZOOM_Z);
	if (keycode == 9)
		data->window.zoom_z = fmax(data->window.zoom_z - 0.5, MIN_ZOOM_Z);
	if (keycode == 45)
		data->window.pitch += 0.05;
	if (keycode == 11)
		data->window.pitch -= 0.05;
}

int	key_hoo(int keycode, t_fdf *data)
{
	if (valid_key(keycode))
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		exec_key(keycode, data);
		draw_map(data);
	}
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free_data(data);
		printf(CYAN BOLD "Work with t_fdf program finished with ESC\n" RESET);
		exit(0);
	}
	if (!valid_key(keycode))
		ft_printf(RED "There is no command for this button\n" RESET);
	return (0);
}
