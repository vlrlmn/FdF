/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:43:00 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 13:04:57 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_and_fill(int fd, t_fdf *data)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line && i < data->height && *line)
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
			return (err_free(line, RED BOLD "Failed fill matrix!\n" RESET));
		free(line);
		i++;
		line = get_next_line(fd);
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

int	read_file(char *filename, t_fdf *data)
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
