/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:41:42 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 17:26:07 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + len - 4, ".fdf", 4) == 0)
		return (0);
	else
		return (1);
}

int	valid_color_format(char *color)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(color);
	if (length >= 2 && (color[0] == '0' && (color[1] == 'x'
				|| color[1] == 'X')))
	{
		color += 2;
		length -= 2;
	}
	else 
		return(1);
	if (length < 2 || length > 6)
		return (1);
	while (i < length)
	{
		if (!(((color[i]) >= '0' && color[i] <= '9') || (color[i] >= 'a'
					&& color[i] <= 'f') || (color[i] >= 'A'
					&& color[i] <= 'F')))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_line(char *line)
{
	int	i;
	int	has_valid_char;

	i = 0;
	has_valid_char = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			has_valid_char = 1;
		else if (line[i] == '\t')
			return (0);
		i++;
	}
	return (has_valid_char);
}

int	is_pair_invalid(char **pair)
{
	if (!is_valid_number(pair[0]))
		return (err_free_arr(free_array, pair,
				RED BOLD "Num invalid error\n" RESET));
	if (pair[1] && valid_color_format(pair[1]))
		return (err_free_arr(free_array, pair,
				RED BOLD "Color invalid error\n" RESET));
	return (0);
}
