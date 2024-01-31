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
    int height;
    int width;
    int **matrix;
    int zoom;
    int color;
    int shift_x;
    int shift_y;
    void    *mlx_ptr;
    void    *win_ptr;
}       fdf;

int read_file(char *filename, fdf *data);
void bresenham(float x, float y, float x1, float y1, fdf *data);
void draw_map(fdf *data);
void isometric(float *x, float *y, int z);

#endif