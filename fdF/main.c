/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:43:10 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 16:49:33 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	default_parameters(t_fdf *data)
{
	data->window.zoom = 20;
	data->window.z_height = 0.9;
	data->window.zoom_z = 1.5;
	data->window.angle = 0.6;
	data->window.pitch = 1.03;
	data->window.win_x = 1500;
	data->window.win_y = 1500;
	data->window.shift_x = data->window.win_x / 3;
	data->window.shift_y = data->window.win_y / 3;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.win_x,
			data->window.win_y, "t_fdf");
	data->gradient.min_color = 0x800080;
	data->gradient.max_color = 0x00ff00;
	data->matrix = NULL;
	data->col_matrix = NULL;
	data->img_string = NULL;
	data->img = NULL;
}

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2 || !argv[1] || check_file(argv[1]))
	{
		ft_printf(RED "Use command ./t_fdf filename.t_fdf\n" RESET);
		exit(1);
	}
	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!data)
		exit(EXIT_FAILURE);
	default_parameters(data);
	if (read_file(argv[1], data))
	{
		free_data(data);
		free(data);
		exit(1);
	}
	draw_map(data);
	mlx_hook(data->win_ptr, 2, 1, key_hoo, data);
	mlx_hook(data->win_ptr, 17, 0L, close_window, data);
	mlx_loop(data->mlx_ptr);
}
