/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:56:41 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 21:45:15 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *data)
{
	ft_printf(CYAN BOLD "Program finished with cross sign\n" RESET);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_data(data);
	exit(0);
}

void	free_matrix(t_fdf *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		if (data->matrix[i])
		{
			free(data->matrix[i]);
			data->matrix[i] = NULL;
		}
		i++;
	}
	free(data->matrix);
	data->matrix = NULL;
}

void	free_color_matrix(t_fdf *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		if (data->col_matrix[i])
		{
			free(data->col_matrix[i]);
			data->col_matrix[i] = NULL;
		}
		i++;
	}
	free(data->col_matrix);
	data->col_matrix = NULL;
}

void	free_data(t_fdf *data)
{
	if (data->matrix)
	{
		free_matrix(data);
	}
	if (data->col_matrix)
	{
		free_color_matrix(data);
	}
}

void	free_array(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		free(array[j]);
		array[j] = NULL;
		j++;
	}
	free(array);
}
