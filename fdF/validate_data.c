#include "fdf.h"

int	check_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + len - 4, ".fdf", 4) == 0)
		return (0);
	else
		return (1);
}

int	valid_color_format(char *color)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(color);
	if (length >= 2 && (color[0] == '0' && (color[1] == 'x'
				|| color[1] == 'X')))
	{
		color += 2;
		length -= 2;
	}
	if (length != 6 && length != 3)
		return (1);
	while (i < length)
	{
		if (!(((color[i]) >= '0' && color[i] <= '9') || (color[i] >= 'a'
					&& color[i] <= 'f') || (color[i] >= 'A'
					&& color[i] <= 'F')))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_line(char *line)
{
	int i;
	int has_valid_char;

	i = 0;
	has_valid_char = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			has_valid_char = 1;
		else if (line[i] == '\t')
			return (0);
		i++;
	}
	return (has_valid_char);
}
