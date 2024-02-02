#include "fdf.h"

float get_max(float a, float b) 
{
    if (a > b)
        return (a);
    else
        return (b);
}

void isometric(float *x, float *y, int z, fdf *data)
{
    float prev_x = *x;

    *x = (prev_x - *y) * cos(data->angle);
    *y = (prev_x + *y) * sin(data->angle) - z * data->z;
}

void bresenham(float x, float y, float x1, float y1, fdf *data) {
    int z;
    int z1;

    z = data->matrix[(int)y][(int)x] * data->zoom_z;
    z1 = data->matrix[(int)y1][(int)x1] * data->zoom_z;
    printf("z: %d\n", z);
    printf("z1: %d\n", z1);
    //---------zoom----------
    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;
    //-------------3D-------
    isometric(&x, &y, z, data);
    isometric(&x1, &y1, z1, data);
    x += data->shift_x;
    y += data->shift_y;
    x1 += data->shift_x;
    y1 += data->shift_y;
    //-----------shift---------
    int start_color = determine_color_based_on_z(z, data);
    int end_color = determine_color_based_on_z(z1, data);
    float max = get_max(fabs(x1 - x), fabs(y1 - y));
    float x_step = (x1 - x) / max;
    float y_step = (y1 - y) / max;

    for (int i = 0; i <= max; i++) {
        int current_color;
        interpolate_color(start_color, end_color, i / max, &current_color);
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, current_color);
        x += x_step;
        y += y_step;
    }
}

void draw_map(fdf *data)
{
    int x;
    int y;

    y = 0;
    while(y < data->height)
    {
        x = 0;
        while(x < data->width)
        {
            if (x < data->width - 1)
                bresenham(x, y, x + 1, y, data);
            if (y < data->height - 1)
                bresenham(x, y, x, y + 1, data);
            x++;
        }
        y++;
    }
}
