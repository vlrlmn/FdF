/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:20:30 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/06 10:54:09 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_integer(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		print_char('-');
		return (print_digit(-n, base) + 1);
	}
	else if (n < base)
	{
		return (print_char(symbols[n]));
	}
	else
	{
		count = print_digit(n / base, base);
		return (count + print_digit(n % base, base));
	}
}
