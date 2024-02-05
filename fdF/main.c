#include "fdf.h"

void default_parameters(fdf *data)
{
    data->window.zoom = 30;
    data->window.z_height = 0.9;
    data->window.zoom_z = 1.5;
    data->window.angle = 0.6;
    data->window.pitch = 1.03;
    data->window.win_x = 1000;
    data->window.win_y = 700;
    data->window.shift_x = data->window.win_x / 3;
    data->window.shift_y = data->window.win_y / 3;
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->window.win_x, data->window.win_y, "FDF");
    data->gradient.min_color = 0x800080;
    data->gradient.max_color = 0x00ff00;
}

int main(int argc, char **argv)
{
    if (!argv[1] || argc != 2)
        exit(EXIT_FAILURE);
    fdf *data;
    data = (fdf*)malloc(sizeof(fdf));
    if (!data)
        exit(EXIT_FAILURE);
    else if (read_file(argv[1], data))
    {
        free(data);
        exit(EXIT_FAILURE);
    }
    default_parameters(data);
    draw_map(data);
    mlx_key_hook(data->win_ptr, key_hoo, data);
    mlx_loop(data->mlx_ptr);
    free(data);
}