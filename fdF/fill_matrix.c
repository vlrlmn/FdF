/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:44:44 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 16:45:55 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**get_pair_arr(char *token)
{
	char	**pair_arr;
	char	*trimmed_token;

	trimmed_token = ft_strtrim(token, "\n");
	if (!trimmed_token || *trimmed_token == '\0')
		return (NULL);
	pair_arr = ft_split(trimmed_token, ',');
	if (!pair_arr)
	{
		ft_printf(RED BOLD "Token split error\n" RESET);
		free(trimmed_token);
		return (NULL);
	}
	if (ft_strchr(trimmed_token, ',') && !pair_arr[1])
	{
		ft_printf(RED BOLD "Invalid color\n" RESET);
		free_array(pair_arr);
		free(trimmed_token);
		return (NULL);
	}
	free(trimmed_token);
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

	pair = get_pair_arr(token);
	if (!pair)
		return (1);
	if (is_pair_invalid(pair))
		return (1);
	*z_line = ft_atoi(pair[0]);
	fill_color(color_line, pair[1]);
	free_array(pair);
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
