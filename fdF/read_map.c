#include "fdf.h"

int is_pair_invalid(char** pair)
{
	if (!is_valid_number(pair[0]))
		return (err_free_arr(free_array, pair, RED BOLD "Num invalid error\n" RESET));
	if (pair[1] && valid_color_format(pair[1]))
		return (err_free_arr(free_array, pair, RED BOLD "Color invalid error\n" RESET));
	return (0);
}

char** get_pair_arr(char *token)
{
	char	**pair_arr;
	char	*trimmed_token;
	
	trimmed_token = ft_strtrim(token, "\n");
	if (!trimmed_token || *trimmed_token == '\0')
		return NULL;
	pair_arr = ft_split(trimmed_token, ',');
	if (!pair_arr)
	{
		ft_printf(RED BOLD "Token split error\n" RESET);
		free(trimmed_token);
		return NULL;
	}
	if(ft_strchr(trimmed_token, ',') && !pair_arr[1])
	{
		ft_printf(RED BOLD "Invalid color\n" RESET);
		free_array(pair_arr);
		free(trimmed_token);
		return NULL;
	}
	free(trimmed_token);
	return pair_arr;
}

void fill_color(unsigned int *color_line, char *color)
{
	if (color)
		*color_line = (unsigned int)ft_strtol(color);
	else
		*color_line = 0;
}

int fill_matrix_value(int *z_line, unsigned int *color_line, char *token)
{
	char	**pair;

	pair = get_pair_arr(token);
	if (!pair)
		return (1);
	if (is_pair_invalid(pair))
		return (1);
	*z_line = ft_atoi(pair[0]);
	fill_color (color_line, pair[1]);
	free_array(pair);
	return(0);
}

int	fill_matrix(int *z_line, unsigned int *color_line, char *line)
{
	char	**tokens;
	int		i;
	
	i = 0;
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_err(RED BOLD "Malloc error\n" RESET));
	while (tokens[i])
	{
		if (fill_matrix_value(z_line + i, color_line + i, tokens[i]))
		{
			free_array(tokens);
			return (1);
		}
		i++;
	}
	free_array(tokens);
	return (0);
}

int	read_and_fill(int fd, fdf *data)
{
	char	*line;
	int		i;

	i = 0;
	while ((line = get_next_line(fd)) && i < data->height && *line)
	{
		if (!is_valid_line(line))
			return (err_free(line, RED BOLD "Unvalid characters!\n" RESET));
		if (i == 0)
			data->width = word_count(line, ' ');
		if (data->width != word_count(line, ' '))
			return (err_free(line, RED BOLD "Not a rectangle!\n" RESET));
		data->matrix[i] = ft_calloc(data->width, sizeof(int));
		data->col_matrix[i] = ft_calloc(data->width, sizeof(unsigned int));
		if (fill_matrix(data->matrix[i], data->col_matrix[i], line))
		{
			free(line);
			return (1);
		}
		free(line);
		i++;
	}
	return ((i != data->height));
}

int	get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (height);
}

int	read_file(char *filename, fdf *data)
{
	int	fd;
	int	result;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
		return (print_err(RED BOLD "File not opened!\n" RESET));
	data->height = get_height(filename);
	if (data->height == 0)
		return (print_err(RED BOLD "File is empty!\n" RESET));
	data->matrix = (int **)ft_calloc(data->height, sizeof(int *));
	if (!data->matrix)
		return (mem_err(fd, RED BOLD "Memory not allocated\n" RESET));
	data->col_matrix = (unsigned int **)ft_calloc(data->height,
			sizeof(unsigned int *));
	if (!data->col_matrix)
		return (mem_err(fd, RED BOLD "Memory not allocated\n" RESET));
	result = read_and_fill(fd, data);
	if (result == 1)
		return (err_and_close(fd));
	close(fd);
	return (result);
}
