/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:10:19 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 12:11:15 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "Libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "printf/libftprintf.h"
# include <err.h>
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

typedef struct float_point
{
	float	x;
	float	y;
}				t_fpoint;

typedef struct int_point
{
	int	x;
	int	y;
}				t_point;

typedef struct gradient
{
	int					color;
	int					current_color;
	int					min_z;
	int					max_z;
	int					start_color;
	int					end_color;
	int					min_color;
	int					max_color;
}						t_colorInfo;

typedef struct rgb
{
	int					min_r;
	int					min_g;
	int					min_b;
	int					max_r;
	int					max_g;
	int					max_b;
	int					r;
	int					g;
	int					b;
	int					start_r;
	int					start_g;
	int					start_b;
	int					end_r;
	int					end_g;
	int					end_b;
}						t_calculateColor;

typedef struct isometric
{
	t_fpoint			step;
	float				max;
	t_fpoint			prev;
	float				scaled_z;
	float				current_y;
}						t_floatPoint;

typedef struct window
{
	t_point				win;
	t_point				shift;
	double				angle;
	double				pitch;
	float				z_height;
	int					zoom;
	float				zoom_z;
}						t_windowParam;

typedef struct data
{
	int					**matrix;
	unsigned int		**col_matrix;
	int					height;
	int					width;
	int					z;
	int					z1;
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img;
	int					bits;
	int					lsize;
	int					endian;
	char				*img_string;
	t_floatPoint		isometric;
	t_windowParam		window;
	t_colorInfo			gradient;
	t_calculateColor	rgb;
}						t_fdf;

void					default_parameters(t_fdf *data);
int						read_file(char *filename, t_fdf *data);
int						read_and_fill(int fd, t_fdf *data);
int						fill_matrix(int *z_line, unsigned int *color_line,
							char *line);
int						word_count(char *str, char c);
int						get_height(char *filename);
void					bresenham(t_fpoint p, t_fpoint p1, t_fdf *data);
void					draw_map(t_fdf *data);
void					isometric_func(t_fpoint *p, t_fdf *data, int z);
int						key_hoo(int keycode, t_fdf *data);
float					get_max(float a, float b);
void					calculate_min_max_z(t_fdf *data);
void					interpolate_color(float step_ratio, int *current_color,
							t_fdf *data);
int						determine_color_based_on_z(int z, t_fdf *data);
void					free_data(t_fdf *data);
int						close_window(t_fdf *data);
void					free_matrix(t_fdf *data);
void					free_color_matrix(t_fdf *data);
void					free_data(t_fdf *data);
int						check_file(char *file);
int						print_err(char *msg);
int						mem_err(int fd, char *msg);
int						err_and_close(int fd);
int						err_free(char *line, char *msg);
unsigned int			ft_strtol(char *color);
int						valid_color_format(char *color);
void					free_array(char **array);
int						is_valid_line(char *line);
int						is_valid_number(char *str);
int						valid_color_format(char *color);
unsigned int			ft_strtol(char *color);
int						err_free_arr(void free_array(char **), char **array,
							char *msg);
int						is_pair_invalid(char **pair);
char					**get_pair_arr(char *token);
void					fill_color(unsigned int *color_line, char *color);
int						fill_matrix_value(int *z_line, unsigned int *color_line,
							char *token);
int						fill_matrix(int *z_line, unsigned int *color_line,
							char *line);
void					determine_colors(t_fdf *data, unsigned int start_c,
							unsigned int end_c);
void					my_mlx_pixel_put(t_fdf *data, int x, int y, int color);
void					color_pixels(t_fdf *data, float x, float y);
void					fill_color(unsigned int *color_line, char *color);
char					**get_pair_arr(char *token);
int						is_pair_invalid(char **pair);
void					make_img(t_fdf *data);
void					set_gradient(unsigned int start_color,
							unsigned int end_color, t_fdf *data);
#endif