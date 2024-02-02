#include "fdf.h"

float get_max(float a, float b) 
{
    if (a > b)
        return (a);
    else
        return (b);
}

float get_min(float a, float b) {
    return (a < b) ? a : b;
}

void isometric(float *x, float *y, int z, fdf *data)
{
    float prev_x = *x;

    *x = (prev_x - *y) * cos(data->angle);
    *y = (prev_x + *y) * sin(data->angle) - z * data->z;
}


void bresenham(float x, float y, float x1, float y1, fdf *data)
{
    float x_step;
    float y_step;
    float max;
    int z;
    int z1;

    z = data->matrix[(int)y][(int)x] * data->zoom_z;
    z1 = data->matrix[(int)y1][(int)x1] * data->zoom_z;
    //---------zoom----------
    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;
    //---------color----------
    data->color = (z || z1) ? 0xe80c0c : 0xffffff;
    data->color = (z != z1) ? 0xfc031c : data->color;
    //-------------3D-------
    isometric(&x, &y, z, data);
    isometric(&x1, &y1, z1, data);
    x += data->shift_x;
    y += data->shift_y;
    x1 += data->shift_x;
    y1 += data->shift_y;
    //-----------shift---------
    x_step = x1 - x;
    y_step = y1 - y;
    max = get_max(fabs(x_step), fabs(y_step));
    x_step /= max;
    y_step /= max;

    while((int)(x - x1) || (int)(y - y1))
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
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
// int get_color(int z, int z1) 
// {
//     if (z || z1)
//         return (0xe80c0c);
//     else
//         return (0xffffff);
// }

// int interpolate_color(int start, int end, float percentage) {
//     if (start == end)
//         return start;
//     int red = ((start >> 16) & 0xFF) + percentage * (((end >> 16) & 0xFF) - ((start >> 16) & 0xFF));
//     int green = ((start >> 8) & 0xFF) + percentage * (((end >> 8) & 0xFF) - ((start >> 8) & 0xFF));
//     int blue = (start & 0xFF) + percentage * ((end & 0xFF) - (start & 0xFF));
//     return (red << 16) | (green << 8) | blue;
// }

// void bresenham(float x, float y, float x1, float y1, fdf *data) {
//     float x_step = x1 - x;
//     float y_step = y1 - y;
//     int z = data->matrix[(int)y][(int)x] * data->zoom_z;
//     int z1 = data->matrix[(int)y1][(int)x1] * data->zoom_z;
//     int start_color = get_color(z, z);
//     int end_color = get_color(z1, z1);
//     float max = get_max(fabs(x_step), fabs(y_step));

//     // Интерполяция координат и цветов
//     x_step /= max;
//     y_step /= max;
//     for (int i = 0; i <= max; i++) {
//         int current_color = interpolate_color(start_color, end_color, get_max(0, get_min(1, (float)i / max)));
//         mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, current_color);
//         x += x_step;
//         y += y_step;
//     }
// }
