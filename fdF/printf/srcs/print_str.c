/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:53:59 by vlomakin          #+#    #+#             */
/*   Updated: 2023/08/03 12:39:16 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
			str = "(null)";
	while (*str)
	{
		if(print_char((int)*str) != 1){
			return (count);
		}
		++count;
		++str;
	}
	return (count);
}
