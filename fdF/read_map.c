#include "fdf.h"

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
    return (has_valid_char);
}

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

int is_valid_number(char *str) 
{
	//ft_printf(GREEN BOLD "  Check value %s\n" RESET, str);
    if (*str == '-' || *str == '+')
        str++;
    if (*str == '\0')
        return 1;
    while (*str) 
	{
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return (1);
}

void free_array(char **array)
{
	int j;
	j = 0;
	while (array[j])
	{
		free(array[j]);
		array[j] = NULL;
		j++;
	}
	free(array);
}

int valid_color_format(char *color)
{
	int i;
	int length;

	i = 0;

	length = ft_strlen(color);
	if (length >= 2 && (color[0] == '0' && (color[1] == 'x' || color[1] == 'X'))) 
	{
        color += 2;
        length -= 2;
    }
	if (length != 6 && length != 3)
        return (1);
	while(i < length)
	{
		if(!(((color[i])>= '0' && color[i] <= '9') || (color[i] >= 'a' && color[i] <= 'f') || (color[i] >= 'A' && color[i] <= 'F')))
			return(1);
		i++;
	}
	return(0);
}

int	fill_matrix(int *z_line, unsigned int *color_line, char *line)
{
    char	**tokens;
    int		i;
	char **pair;
	char *num;
	char *color;
	char *token;
	char *hasComma;
	
    i = 0;
    tokens = ft_split(line, ' ');
	if(!tokens)
	{
		ft_printf(RED BOLD "Malloc error\n" RESET);
		return (1);
	}
    while (tokens[i])
	{
	    //ft_printf(GREEN BOLD "Got token %s\n" RESET, tokens[i]);

		token = ft_strtrim(tokens[i], "\n");
		if (!token || *token == '\0')
			break;

		pair = ft_split(token, ',');
        hasComma = ft_strchr(token,',');
		free(token);

		//ft_printf(GREEN BOLD "  Got pair %s\n" RESET, *pair);
		if(!pair)
		{
			ft_printf(RED BOLD "Malloc error\n" RESET);
			return (1);
		}

		num = pair[0];
		if (!is_valid_number(num))
		{
			ft_printf(RED BOLD "INVALID CHARS\n" RESET);
			free_array(pair);
			return (1);
		}
		z_line[i] = ft_atoi(num);

		color = pair[1];
		if (color && !valid_color_format(color))
		{
			color_line[i] = (unsigned int)strtol(color, NULL, 16); //write my own strtol
		}
		else if (hasComma || (color && valid_color_format(color)))
		{
			ft_printf(RED BOLD"Check the color format\n" RESET);
			free_array(pair);
			return(1);
		}
		else
			color_line[i] = 0;
		free_array(pair);
		i++;
	}
    free_array(tokens);
	return(0);
}

int read_and_fill(int fd, fdf *data)
{
    char *line;
    int i;
	
	i = 0;
    while ((line = get_next_line(fd)) && i < data->height && *line)
    {
        if (!is_valid_line(line))
        {
            ft_printf(RED BOLD "There are unvalid characters!\n" RESET);
            free(line);
            return (1);
        }
        if (i == 0)
            data->width = word_count(line, ' ');
		if (data->width != word_count(line, ' '))
		{
			ft_printf(RED BOLD "Not a rectangle!\n" RESET);
			free(line);
            return (1);
		}
        data->matrix[i] = ft_calloc(data->width, sizeof(int));
        data->color_matrix[i] = ft_calloc(data->width, sizeof(unsigned int));
        if(fill_matrix(data->matrix[i], data->color_matrix[i], line))
		{
			free(line);
			return(1);
		}
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
        ft_printf(RED BOLD "Memory allocation failed\n" RESET);
		close(fd);
        return (1);
    }

	data->color_matrix = (unsigned int **)ft_calloc(data->height, sizeof(unsigned int *));
	if (!data->color_matrix)
	{
		ft_printf(RED BOLD "Memory allocation failed\n" RESET);
		close(fd);
		return (1);
	}

	result = read_and_fill(fd, data);
	if (result == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (result);
}
