#include "fdf.h"

void	default_parameters(fdf *data)
{
	data->window.zoom = 30;
	data->window.z_height = 0.9;
	data->window.zoom_z = 1.5;
	data->window.angle = 0.6;
	data->window.pitch = 1.03;
	data->window.win_x = 1700;
	data->window.win_y = 1700;
	data->window.shift_x = data->window.win_x / 4;
	data->window.shift_y = data->window.win_y / 4;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.win_x,
			data->window.win_y, "FDF");
	data->gradient.min_color = 0x800080;
	data->gradient.max_color = 0x00ff00;
}

int	close_window(fdf *data)
{
	ft_printf(CYAN BOLD "Work with fdf program finished with cross sign\n" RESET);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_data(data);
	free(data);
	exit(0);
}

int check_file(char *file)
{
    int len;

    len = ft_strlen(file);
    if (ft_strncmp(file + len - 4, ".fdf", 4) == 0)
        return (0);
    else
	    return (1);
}

int	main(int argc, char **argv)
{
    if (argc != 2 || !argv[1] || check_file(argv[1]))
    {
		return (ft_printf(RED "Use command ./fdf filename.fdf\n" RESET));
        exit(1);
    }
	// check if file is valid and args are correct
	fdf *data;
	data = (fdf *)malloc(sizeof(fdf));
	if (!data)
		exit(EXIT_FAILURE);
	else if (read_file(argv[1], data))
	{
		free(data);
		exit(1);
	}
	default_parameters(data);
	draw_map(data);
	mlx_hook(data->win_ptr, 2, 1, key_hoo, data);
	mlx_hook(data->win_ptr, 17, 0L, close_window, data);
	mlx_loop(data->mlx_ptr);
}