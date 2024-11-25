/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlomakin <vlomakin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:16:10 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 12:07:11 by vlomakin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count += print_pointer(va_arg(ap, unsigned long int));
	else if (specifier == 'd' || specifier == 'i')
		count += print_digit((long)va_arg(ap, int), 10);
	else if (specifier == 'u')
		count += print_unsigned((unsigned int)va_arg(ap, int), 10);
	else if (specifier == 'x')
		count += print_hex((unsigned int)va_arg(ap, int), 16, 'x');
	else if (specifier == 'X')
		count += print_hex((unsigned int)va_arg(ap, int), 16, 'X');
	else if (specifier == '%')
		return (print_char('%'));
	else
		count += write(1, &specifier, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		res;

	va_start(ap, format);
	count = 0;
	if (format == NULL)
		return (-1);
	while (*format)
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
		{
			res = write(1, format, 1);
			if (res != 1)
				count = -1;
			else
				count += res;
		}
		++format;
	}
	va_end(ap);
	return (count);
}
