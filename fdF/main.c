#include "fdf.h"

int	key_hook(int keycode, fdf *data)
{
	printf("Hello from key_hook %d!\n", keycode);
    if (keycode == 126)
        data->shift_y -= 10;
    if (keycode == 125)
        data->shift_y += 10;
    if (keycode == 124)
        data->shift_x += 10;
    if (keycode == 123)
        data->shift_x -= 10;
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw_map(data);
	return (0);
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

    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 700, "FDF");
    data->zoom = 30;
    // bresenham(10, 10, 600, 300, data);
    draw_map(data);
    mlx_key_hook(data->win_ptr, key_hook, data);
    mlx_loop(data->mlx_ptr);
}

//     int i, j;
//     i = 0;
//     while(i < data->height)
//     {
//         j = 0;
//         while(j < data->width)
//         {
//             printf("%3d", data->matrix[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }

//     for (i = 0; i < data->height; i++) {
//         free(data->matrix[i]);  
//     }
//     free(data->matrix);
//     free(data);
//     return 0;
// }
