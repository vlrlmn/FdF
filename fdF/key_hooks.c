#include "fdf.h"

int valid_key(int keycode)
{
    return(keycode >= 0 && keycode <= 130);
}

void exec_key(int keycode, fdf *data)
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
}

int	key_hoo(int keycode, fdf *data)
{
    if(valid_key(keycode))
    {
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        exec_key(keycode, data);
        draw_map(data);
    }
    if (keycode == 53)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data);
        exit(0);
    }
    return(0);
}