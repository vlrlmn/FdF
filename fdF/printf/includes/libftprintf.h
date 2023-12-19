/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:18:30 by vlomakin          #+#    #+#             */
/*   Updated: 2023/08/02 12:36:47 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	print_char(int c);
int	print_digit(long n, int base);
int	print_str(char *str);
int	print_integer(long n, int base);
int	print_pointer(unsigned long int n);
int	print_unsigned(unsigned int n, unsigned int base);
int	print_hex(unsigned long n, unsigned int base, char flag);

#endif