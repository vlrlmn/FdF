#ifndef FDF_H
#define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>
#include "minilibx_macos/mlx.h"
#include "Libft/libft.h"


#define ERROR_MESSAGE "Please write the names correct"

typedef struct
{
    int height;
    int width;
    int **matrix;
}           fdf;

void read_file(char *filename, fdf *data);

#endif