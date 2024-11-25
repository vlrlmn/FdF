/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:12:21 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 12:07:26 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_pointer(unsigned long int n)
{
	int	count;

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
	return (count + 2);
}
