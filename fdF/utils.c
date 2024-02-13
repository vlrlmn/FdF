/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:41:56 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/13 22:33:29 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	word_count(char *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] && str[i] != '\n')
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

unsigned int	ft_strtol(char *color)
{
	char			*hex;
	unsigned long	result;
	char			*ptr;

	hex = "0123456789abcdef";
	result = 0;
	if (color[0] == '0' && (color[1] == 'x' || color[1] == 'X'))
		color += 2;
	while (*color != '\0')
	{
		ptr = ft_strchr(hex, *color);
		if (ptr == NULL)
			break ;
		result = result * 16 + (ptr - hex);
		color++;
	}
	return (result);
}

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < data->window.win.x && y >= 0 && y < data->window.win.y)
	{
		dst = data->img_string + (y * data->lsize + x * (data->bits / 8));
		*(unsigned int *)dst = color;
	}
}

float	get_max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
