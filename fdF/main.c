#include "fdf.h"

void default_parameters(fdf *data, colorInfo *gradient)
{
    data->zoom = 30;
    data->z = 1.5;
    data->zoom_z = 1.5;
    data->angle = 0.523599;
    data->win_x = 1000;
    data->win_y = 700;
    data->shift_x = data->win_x / 3;
    data->shift_y = data->win_y / 3;
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_x, data->win_y, "FDF");
    gradient->min_color = 0x800080;
    gradient->max_color = 0x00ff00;
}

int main(int argc, char **argv)
{
    if (!argv[1] || argc != 2)
        exit(EXIT_FAILURE);
    colorInfo *gradient;
    gradient = (colorInfo*)malloc(sizeof(colorInfo));
    if (!gradient)
        exit(EXIT_FAILURE);
    fdf *data;
    data = (fdf*)malloc(sizeof(fdf));
    if (!data)
        exit(EXIT_FAILURE);
    else if (read_file(argv[1], data))
    {
        free(data);
        free(gradient);
        exit(EXIT_FAILURE);
    }
    default_parameters(data, gradient);
    draw_map(data);
    mlx_key_hook(data->win_ptr, key_hoo, data);
    mlx_loop(data->mlx_ptr);
    free(data);
    free(gradient);
}