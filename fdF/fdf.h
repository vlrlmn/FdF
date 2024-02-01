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
    int zoom_z;
    int color;
    int win_x;
    int win_y;
    int shift_x;
    int shift_y;
    double angle;
    void    *mlx_ptr;
    void    *win_ptr;
}       fdf;

void default_parameters(fdf *data);
int	key_hoo(int keycode, fdf *data);
int read_file(char *filename, fdf *data);
int read_and_fill(int fd, fdf *data);
void fill_matrix(int *z_line, char *line);
int	ft_wdcounter(char const *str, char c);
int get_height(char *filename);
void bresenham(float x, float y, float x1, float y1, fdf *data);
void draw_map(fdf *data);
void isometric(float *x, float *y, int z, fdf *data);
int	key_hoo(int keycode, fdf *data);

#endif