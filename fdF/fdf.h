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

typedef struct
{
    float x;
    float y;
    float z;
    int height;
    int width;
    int **matrix;
    int zoom;
    float zoom_z;
    int win_x;
    int win_y;
    int shift_x;
    int shift_y;
    double angle;
    void    *mlx_ptr;
    void    *win_ptr;
    int min_z;
    int max_z;
}       fdf;

typedef struct
{
    int color;
    int min_z;
    int max_z;
    unsigned int min_color;
    unsigned int max_color;
}       colorInfo;


void default_parameters(fdf *data, colorInfo *gradient);
int read_file(char *filename, fdf *data);
int read_and_fill(int fd, fdf *data);
void fill_matrix(int *z_line, char *line);
int	word_count(char const *str, char c);
int get_height(char *filename);
void bresenham(float x, float y, float x1, float y1, fdf *data);
void draw_map(fdf *data);
void isometric(float *x, float *y, int z, fdf *data);
int	key_hoo(int keycode, fdf *data, colorInfo *gradient);
float get_max(float a, float b);
void change_window(int keycode, fdf *data);
void new_size(int keycode, fdf *data);
int get_min_z(fdf *data);
int get_max_z(fdf *data);
void interpolate_color(int start_color, int end_color, float step_ratio, int *current_color);
int determine_color_based_on_z(int z, fdf *data, colorInfo *gradient);

#endif