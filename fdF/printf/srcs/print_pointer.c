/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:12:21 by vlomakin          #+#    #+#             */
/*   Updated: 2023/08/02 12:37:44 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

int	print_pointer(unsigned long int n)
{
	int		count;
	
	count = 0;
	write(1, "0x", 2);
	if (n == 0)
	{
		write(1, "0", 1);
		return (count + 3);
	}
	else
	{
		count = print_hex(n, 16, 'x');
	}
		return(count + 2);
}