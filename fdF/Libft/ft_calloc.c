/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:51 by vlomakin          #+#    #+#             */
/*   Updated: 2023/12/18 17:58:15 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	amount;

	if (size && count > SIZE_MAX / size)
        return (NULL);
	amount = count * size;
	ptr = malloc(amount);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, amount);
	return (ptr);
}
