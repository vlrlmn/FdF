/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:53:59 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/06 10:54:12 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		if (print_char((int)*str) != 1)
		{
			return (count);
		}
		++count;
		++str;
	}
	return (count);
}
