#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "printf/libftprintf.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR_MESSAGE "Please write the names correct"
# define MAX_ZOOM_Z 200
# define MIN_ZOOM_Z -20
# define RED "\033[1;31m"
# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define BACK "\033[47m"

typedef struct
{
	int				color;
	int				current_color;
	int				min_z;
	int				max_z;
	int				start_color;
	int				end_color;
	int				min_color;
	int				max_color;
}					colorInfo;

typedef struct
{
	int				min_r;
	int				min_g;
	int				min_b;
	int				max_r;
	int				max_g;
	int				max_b;
	int				r;
	int				g;
	int				b;
	int				start_r;
	int				start_g;
	int				start_b;
	int				end_r;
	int				end_g;
	int				end_b;
}					calculateColor;

typedef struct
{
	float			x_step;
	float			y_step;
	float			max;
	float			prev_x;
	float			prev_y;
	float			scaled_z;
	float			current_y;
}					floatPoint;

typedef struct
{
	int				win_x;
	int				win_y;
	int				shift_x;
	int				shift_y;
	double			angle;
	double			pitch;
	float			z_height;
	int				zoom;
	float			zoom_z;
}					windowParam;

typedef struct
{
	int				**matrix;
	int				height;
	int				width;
	int				z;
	int				z1;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	int				bits;
	int				lsize;
	int				endian;
	char			*img_string;
	floatPoint		isometric;
	windowParam		window;
	colorInfo		gradient;
	calculateColor	rgb;
}					fdf;

void				default_parameters(fdf *data);
int					read_file(char *filename, fdf *data);
int					read_and_fill(int fd, fdf *data);
void				fill_matrix(int *z_line, char *line);
int					word_count(char *str, char c);
int					get_height(char *filename);
void				bresenham(float x, float y, float x1, float y1, fdf *data);
void				draw_map(fdf *data);
void				isometric_func(float *x, float *y, fdf *data, int z);
int					key_hoo(int keycode, fdf *data);
float				get_max(float a, float b);
void 				calculate_min_max_z(fdf *data);
void				interpolate_color(float step_ratio, int *current_color,
						fdf *data);
int					determine_color_based_on_z(int z, fdf *data);
void				color_pixels(fdf *data, float x, float y);
void				free_data(fdf *data);
int					close_window(fdf *data);

#endif