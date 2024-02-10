#include "fdf.h"

int	get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (height);
}

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

// int is_valid_number(char *str) 
// {
//     if (*str == '-' || *str == '+')
//         str++;
//     if (*str == '\0')
//         return 0;
//     while (*str) 
// 	{
//         if (*str < '0' || *str > '9')
//             return 1;
//         str++;
//     }
//     return (0);
// }

int	fill_matrix(int *z_line, unsigned int *color_line, char *line)
{
    char	**nums;
    int		i;
	char **parts;
	int j;

    i = 0;
	j = 0;
    nums = ft_split(line, ' ');
	if(!nums)
	{
		ft_printf(RED BOLD "Malloc error\n" RESET);
		return (1);
	}
    while (nums[i])
	{
		// if (!is_valid_number(nums[i]))
		// {
		// 	ft_printf(RED BOLD "INVALID CHARS\n" RESET);
		// 	return (1);
		// }
		parts = ft_split(nums[i], ',');
		if(!parts)
		{
			ft_printf(RED BOLD "Malloc error\n" RESET);
			return (1);
		}
		z_line[i] = ft_atoi(parts[0]);
		if (parts[1])
			color_line[i] = (unsigned int)strtol(parts[1], NULL, 16); //write my own strtol
		else
			color_line[i] = 0;
		j = 0;
		while (parts[j])
		{
			free(parts[j]);
			j++;
		}
		free(parts);
		free(nums[i]);
		i++;
	}
    free(nums);
	return(0);
}

int is_valid_line(char *line)
{
    int i = 0;
    int has_valid_char = 0;

    while (line[i] && line[i] != '\n')
    {
        if (line[i] != ' ' && line[i] != '\t')
            has_valid_char = 1;
        else if (line[i] == '\t')
            return 0;
        i++;
    }
    return has_valid_char;
}

int read_and_fill(int fd, fdf *data)
{
    char *line;
    int i;
	
	i = 0;
    data->color_matrix = ft_calloc(sizeof(unsigned int *), data->height);
	if (!data->color_matrix)
	{
		ft_printf(RED BOLD "Memory allocation failed\n" RESET);
		while (i-- > 0) 
		{
			free(data->matrix[i]);
			free(data->color_matrix[i]);
		}
		free(data->matrix);
		free(data->color_matrix);
		close(fd);
		return (1);
	}
    while ((line = get_next_line(fd)) && i < data->height && *line)
    {
        if (!is_valid_line(line))
        {
            ft_printf(RED BOLD "There are unvalid characters!\n" RESET);
            free(line);
            while (i-- > 0) 
			{
                free(data->matrix[i]);
                free(data->color_matrix[i]);
            }
            free(data->matrix);
            free(data->color_matrix);
            return (1);
        }
        if (i == 0)
            data->width = word_count(line, ' ');
		if (data->width != word_count(line, ' '))
		{
			ft_printf(RED BOLD "Not a rectangle!\n" RESET);
            free(line);
            while (i-- > 0) 
			{
                free(data->matrix[i]);
                free(data->color_matrix[i]);
            }
            free(data->matrix);
            free(data->color_matrix);
            return (1);
		}
        data->matrix[i] = ft_calloc(sizeof(int), data->width);
        data->color_matrix[i] = ft_calloc(sizeof(unsigned int), data->width);
        if(fill_matrix(data->matrix[i], data->color_matrix[i], line))
			return(1);
		free(line);
		i++;

    }
    return ((i != data->height));
}


int	read_file(char *filename, fdf *data)
{
	int	fd;
	int	result;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		ft_printf(RED BOLD "File cannot be opened!\n" RESET);
		return (1);
	}
	data->height = get_height(filename);
	if (data->height == 0) 
	{
		ft_printf(RED BOLD "File is empty!\n" RESET);
		return (1);
	}
	data->matrix = (int **)ft_calloc(data->height, sizeof(int *));
    if (!data->matrix) 
	{
        close(fd);
        return (1);
    }
	result = read_and_fill(fd, data);
	close(fd);
	return (result);
}
