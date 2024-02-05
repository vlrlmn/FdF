#ifndef FDF_H
#define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>
#include "minilibx_macos/mlx.h"
#include "libft/libft.h"

#define ERROR_MESSAGE "Please write the names correct"
#define MAX_ZOOM_Z 10
#define MIN_ZOOM_Z -10

typedef struct
{
    int color;
    int current_color;
    int min_z;
    int max_z;
    unsigned int start_color;
    unsigned int end_color;
    unsigned int min_color;
    unsigned int max_color;
}       colorInfo;

typedef struct
{
    int min_r;
    int min_g;
    int min_b;
    int max_r;
    int max_g;
    int max_b;
    int r;
    int g;
    int b;
}   calculateColor;

typedef struct
{
    float x_step;
    float y_step;
    float max;
} floatPoint;

typedef struct
{
    int x;
    int y;
} intPoint;

typedef struct
{
    int win_x;
    int win_y;
    int shift_x;
    int shift_y;
    double angle;
    double pitch;
    float z_height;
    int zoom;
    float zoom_z;
} windowParam;

typedef struct
{
    int **matrix;
    int height;
    int width;
    int z;
    int z1;
    void    *mlx_ptr;
    void    *win_ptr;
    floatPoint bresenStep;
    windowParam window;

    colorInfo gradient;
    calculateColor rgb;
}       fdf;


void default_parameters(fdf *data);
int read_file(char *filename, fdf *data);
int read_and_fill(int fd, fdf *data);
void fill_matrix(int *z_line, char *line);
int	word_count(char const *str, char c);
int get_height(char *filename);
void bresenham(float x, float y, float x1, float y1, fdf *data);
void draw_map(fdf *data);
void isometric(float *x, float *y, fdf *data, int z);
int	key_hoo(int keycode, fdf *data);
float get_max(float a, float b);
void change_window(int keycode, fdf *data);
void new_size(int keycode, fdf *data);
int get_min_z(fdf *data);
int get_max_z(fdf *data);
void interpolate_color(int start_color, int end_color, float step_ratio, int *current_color);
int determine_color_based_on_z(int z, fdf *data);
void color_pixels(fdf *data, float x, float y);
#endif