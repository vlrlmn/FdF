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
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

unsigned int	ft_strtol(char *color)
{
	char *hex;
	unsigned long result;
	char *ptr;

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