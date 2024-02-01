#include "fdf.h"

int	key_hoo(int keycode, fdf *data)
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