/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomakinavaleria <lomakinavaleria@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:23:29 by vlomakin          #+#    #+#             */
/*   Updated: 2024/02/14 17:03:57 by lomakinaval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	words;
	int	counter;

	words = 0;
	counter = 0;
	while (*s)
	{
		if (*s != c && counter == 0)
		{
			counter = 1;
			words++;
		}
		else if (*s == c)
		{
			counter = 0;
		}
		s++;
	}
	return (words);
}

int	word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			s++;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

char	**copy_words(char const *s, char c, int words, char **result)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		word_len = word_length(&s[j], c);
		result[i] = malloc(sizeof(char) * (word_len + 1));
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		ft_strlcpy(result[i], &s[j], word_len + 1);
		j += word_len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!words)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	if (!copy_words(s, c, words, result))
		return (NULL);
	return (result);
}
