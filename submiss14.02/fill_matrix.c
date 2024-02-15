/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:44:44 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 16:57:17 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**get_pair_arr(char *token)
{
	char	**pair_arr;

	pair_arr = ft_split(token, ',');
	if (!pair_arr)
	{
		ft_printf(RED BOLD "Token split error\n" RESET);
		return (NULL);
	}
	if (ft_strchr(token, ',') && !pair_arr[1])
	{
		ft_printf(RED BOLD "Invalid color\n" RESET);
		free_array(pair_arr);
		return (NULL);
	}
	return (pair_arr);
}

void	fill_color(unsigned int *color_line, char *color)
{
	if (color)
		*color_line = (unsigned int)ft_strtol(color);
	else
		*color_line = 0;
}

int	fill_matrix_value(int *z_line, unsigned int *color_line, char *token)
{
	char	**pair;
	char	*trimmed_token;

	trimmed_token = ft_strtrim(token, "\n ");
	if (!trimmed_token || *trimmed_token == '\0')
	{
		free(trimmed_token);
		return (0);
	}
	pair = get_pair_arr(trimmed_token);
	if (!pair)
		return (print_err(RED BOLD "Empty pair!\n" RESET));
	if (is_pair_invalid(pair))
		return (err_free(trimmed_token, RED BOLD "Invalid pair!\n" RESET));
	*z_line = ft_atoi(pair[0]);
	fill_color(color_line, pair[1]);
	free_array(pair);
	free(trimmed_token);
	return (0);
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
