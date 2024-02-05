#include "fdf.h"

float get_max(float a, float b) 
{
    if (a > b)
        return (a);
    else
        return (b);
}

void isometric(float *x, float *y, fdf *data, int z)
{
    float prev_x = *x;
    float prev_y = *y;

    // Вращение вокруг оси Z (влево/вправо)
    *x = prev_x * cos(data->window.angle) - prev_y * sin(data->window.angle);
    *y = prev_x * sin(data->window.angle) + prev_y * cos(data->window.angle);

    // Масштабирование координаты Z
    float scaled_z = z * data->window.z_height;

    // Сохранение промежуточного значения Y перед вращением вокруг оси X
    float intermediate_y = *y;

    // Вращение вокруг оси X (вверх/вниз)
    *y = intermediate_y * cos(data->window.pitch) - scaled_z * sin(data->window.pitch);
}

void color_pixels(fdf *data, float x, float y)
{
    int i;
    i = 0;
    while (i <= data->bresenStep.max)
    {
        interpolate_color(data->gradient.start_color, data->gradient.end_color, i / data->bresenStep.max, &data->gradient.current_color);
        if (x >= 0 && x < data->window.win_x && y >= 0 && y < data->window.win_y)
        {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->gradient.current_color);
            x += data->bresenStep.x_step;
            y += data->bresenStep.y_step;
            i++;
        }
        else
            return ;
    }
}
void bresenham(float x, float y, float x1, float y1, fdf *data) 
{
    data->z = data->matrix[(int)y][(int)x] * data->window.zoom_z;
    data->z1 = data->matrix[(int)y1][(int)x1] * data->window.zoom_z;
    x *= data->window.zoom;
    y *= data->window.zoom;
    x1 *= data->window.zoom;
    y1 *= data->window.zoom;
    isometric(&x, &y, data, data->z);
    isometric(&x1, &y1, data, data->z1);
    x += data->window.shift_x;
    y += data->window.shift_y;
    x1 += data->window.shift_x;
    y1 += data->window.shift_y;
    data->gradient.start_color = determine_color_based_on_z(data->z, data);
    data->gradient.end_color = determine_color_based_on_z(data->z1, data);
    data->bresenStep.max = get_max(fabs(x1 - x), fabs(y1 - y));
    data->bresenStep.x_step = (x1 - x) / data->bresenStep.max;
    data->bresenStep.y_step = (y1 - y) / data->bresenStep.max;

    color_pixels(data, x, y);
 
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
