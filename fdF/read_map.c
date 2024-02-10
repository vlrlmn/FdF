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

void	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	i = 0;
	nums = ft_split(line, ' ');
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
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
    int i = 0;

    while ((line = get_next_line(fd)) && i < data->height && *line)
    {
        if (!is_valid_line(line))
        {
            ft_printf(RED BOLD "There are unvalid characters!\n" RESET);
            free(line);
            while (i-- > 0)
                free(data->matrix[i]);
            free(data->matrix);
            return 1;
        }

        if (i == 0)
            data->width = word_count(line, ' ');
        data->matrix[i] = ft_calloc(sizeof(int), data->width);
        fill_matrix(data->matrix[i], line);
        free(line);
        i++;
    }
    return ((i != data->height));
}

// int	read_and_fill(int fd, fdf *data)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	while ((line = get_next_line(fd)) && i < data->height && *line)
// 	{
// 		if (i == 0)
// 			data->width = word_count(line, ' ');
// 		data->matrix[i] = ft_calloc(sizeof(int), data->width);
// 		fill_matrix(data->matrix[i], line);
// 		free(line);
// 		i++;
// 	}
// 	return ((i != data->height));
// }

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
		return 1;
	}
	data->matrix = ft_calloc(sizeof(int *), data->height);
	if (!data->matrix)
	{
		close(fd);
		return (1);
	}
	result = read_and_fill(fd, data);
	close(fd);
	return (result);
}


// int	get_height(char *filename)
// {
//     int		fd;
//     int		height;
//     char	*line;
//     char	*trimmed_line;

//     height = 0;
//     fd = open(filename, O_RDONLY, 0);
//     if (fd < 0)
//         return (-1);
//     while ((line = get_next_line(fd)))
//     {
//         trimmed_line = ft_strtrim(line, " \t\n");
//         if (trimmed_line && *trimmed_line)
//             height++;
//         free(trimmed_line);
//         free(line);
//     }
//     close(fd);
//     return (height);
// }


// int is_hex_digit(char c) 
// {
//     return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
// }

// int check_valid(char *str, int len) {
//     int i = 0;
    
//     // Пропуск пробельных символов
//     while (i < len && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) 
//         i++;
//     // Проверка на отрицательное число
//     if (i < len && str[i] == '-') 
//         i++;
//     // Проверка на шестнадцатеричное число
//     if (i + 2 < len && str[i] == '0' && (str[i+1] == 'x' || str[i+1] == 'X')) {
//         i += 2;
//         if (i == len) return 1; // Нет цифр после "0x" или "0X"
//         while (i < len) {
//             if (!is_hex_digit(str[i])) 
//                 return 1;
//             i++;
//         }
//     } else {
//         if (i == len) return 1; // Строка состоит только из пробелов или "-"
//         while (i < len) {
//             if (!ft_isdigit(str[i])) 
//                 return 1;
//             i++;
//         }
//     }
//     return 0; // Данные валидны
// }


// int word_count(char *str, char c) 
// {
//     int i = 0;
//     int words = 0;
//     int start, end;

//     while (str[i]) 
// 	{
//         while (str[i] == c && str[i] != '\0') 
// 			i++;
//         start = i;
//         while (str[i] != c && str[i] != '\0') 
// 			i++;
//         end = i;
//         if (start < end) 
// 		{
// 			while (start < end && str[start] == ' ') 
// 				start++;
// 			while (end > start && str[end - 1] == ' ') 
// 				end--;
// 			if (start < end) 
// 			{
// 				if (check_valid(&str[start], end - start)) 
// 				{
// 					printf("Returning due to check_valid failure: %d\n", -1);
// 					return (-1);
// 				}
//         		words++;
//     		}
// 		}
//     }
//     printf("%d\n", words);
//     return words;
// }

// void	fill_matrix(int *z_line, char *line)
// {
// 	char	**nums;
// 	int		i;

// 	i = 0;
// 	nums = ft_split(line, ' ');
// 	while (nums[i])
// 	{
// 		z_line[i] = ft_atoi(nums[i]);
// 		free(nums[i]);
// 		i++;
// 	}
// 	free(nums);
// }

// int	read_and_fill(int fd, fdf *data)
// {
// 	char	*line;
// 	int		i;
// 	int current_width;

// 	i = 0;
	
// 	while ((line = get_next_line(fd)) && i < data->height && *line)
// 	{
// 		current_width = word_count(line, ' ');
// 		if (current_width == -1)
// 		{
// 			ft_printf(RED BOLD "Invalid data in file\n" RESET);
// 			free(line);
// 			return (1);
// 		}
// 		if (i == 0)
// 			data->width = current_width;
// 		else if (data->width != current_width)
// 		{
// 			ft_printf(RED BOLD "Map should be a rectangle!\n" RESET);
// 			free(line);
// 			return (1);
// 		}
// 		data->matrix[i] = ft_calloc(sizeof(int), data->width);
// 		if (!data->matrix[i])
// 		{
// 			free(line);
// 			return (1);
// 		}
// 		fill_matrix(data->matrix[i], line);
// 		free(line);
// 		i++;
// 	}
// 	return ((i != data->height));
// }

// int	read_file(char *filename, fdf *data)
// {
// 	int	fd;
// 	int	result;

// 	fd = open(filename, O_RDONLY, 0);
// 	if (fd < 0)
// 	{
// 		ft_printf(RED BOLD "File cannot be opened!\n" RESET);
// 		return (1);
// 	}
// 	data->height = get_height(filename);
// 	if (data->height == 0)
// 	{
// 		ft_printf(RED BOLD"Seems you have an empty file!\n" RESET);
// 		return(1);
// 	}
// 	data->matrix = ft_calloc(sizeof(int *), data->height);
// 	if (!data->matrix)
// 	{
// 		close(fd);
// 		return (1);
// 	}
// 	result = read_and_fill(fd, data);
// 	close(fd);
// 	return (result);
// }
