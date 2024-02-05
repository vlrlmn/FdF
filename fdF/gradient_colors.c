#include "fdf.h"

void interpolate_color(int start_color, int end_color, float step_ratio, int *current_color) {
    int start_r = (start_color >> 16) & 0xFF;
    int start_g = (start_color >> 8) & 0xFF;
    int start_b = start_color & 0xFF;

    int end_r = (end_color >> 16) & 0xFF;
    int end_g = (end_color >> 8) & 0xFF;
    int end_b = end_color & 0xFF;

    int r = (int)(start_r + (end_r - start_r) * step_ratio);
    int g = (int)(start_g + (end_g - start_g) * step_ratio);
    int b = (int)(start_b + (end_b - start_b) * step_ratio);

    *current_color = (r << 16) | (g << 8) | b;
}

int get_min_z(fdf *data) {
    int min_z = INT_MAX;
    for (int y = 0; y < data->height; y++) {
        for (int x = 0; x < data->width; x++) {
            if (data->matrix[y][x] < min_z) {
                min_z = data->matrix[y][x];
            }
        }
    }
    return min_z;
}

int get_max_z(fdf *data) {
    int max_z = INT_MIN;
    for (int y = 0; y < data->height; y++) {
        for (int x = 0; x < data->width; x++) {
            if (data->matrix[y][x] > max_z) {
                max_z = data->matrix[y][x];
            }
        }
    }
    return max_z;
}


int determine_color_based_on_z(int z, fdf *data) 
{
    data->gradient.min_z = get_min_z(data);
    data->gradient.max_z = get_max_z(data);

    // Normalize z-value to a range of 0 to 1 (you might need to adjust this based on your actual z range)
    float normalized_z = (float)(z - data->gradient.min_z) / (data->gradient.max_z - data->gradient.min_z);

    // Decompose min and max colors into their components
    data->rgb.min_r = (data->gradient.min_color >> 16) & 0xFF;
    data->rgb.min_g = (data->gradient.min_color >> 8) & 0xFF;
    data->rgb.min_b = data->gradient.min_color & 0xFF;
    data->rgb.max_r = (data->gradient.max_color >> 16) & 0xFF;
    data->rgb.max_g = (data->gradient.max_color >> 8) & 0xFF;
    data->rgb.max_b = data-> gradient.max_color & 0xFF;

    // Calculate the color components based on the normalized z-value
    int r = data->rgb.min_r + (int)(normalized_z * (data->rgb.max_r - data->rgb.min_r));
    int g = data->rgb.min_g + (int)(normalized_z * (data->rgb.max_g - data->rgb.min_g));
    int b = data->rgb.min_b + (int)(normalized_z * (data->rgb.max_b - data->rgb.min_b));

    // Combine the color components back into a single integer
    return (r << 16) | (g << 8) | b;
}

// void color_pixels(int x, int y, fdf *data)
// {
//     int i;

//     i = 0;
//     data->gradient.start_color = determine_color_based_on_z(data);
//     data->gradient.end_color = determine_color_based_on_z(data);
//     while (i <= data->bresenStep.max)
//     {
//         interpolate_color(data->gradient.start_color, data->gradient.end_color, i / data->bresenStep.max, &data->gradient.current_color);
//         mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->gradient.current_color);
//         x += data->bresenStep.x_step;
//         y += data->bresenStep.y_step;
//         i++;
//     }
// }