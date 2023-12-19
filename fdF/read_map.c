#include "fdf.h"

int get_height(char *filename)
{
    int fd;
    int height;
    char *line;

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
    return(height);
}

int		ft_wdcounter(char const *str, char c)
{
	int i;
	int words;

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

void fill_matrix(int *z_line, char *line)
{
    char **nums;
    int i;

    i = 0;
    nums = ft_split(line, ' ');
    while(nums[i])
    {
        z_line[i] = ft_atoi(nums[i]);
        free(nums[i]);
        i++;
    }
    free(nums);
}

void read_file(char *filename, fdf *data)
{
    int fd;
    char *line;
    int i = 0;

    fd = open(filename, O_RDONLY, 0);
    if (fd < 0) 
    { 
        return ;
    }
    data->height = get_height(filename);  // Вызывается только для вычисления высоты
    data->matrix = ft_calloc(sizeof(int*), data->height);
    if (!data->matrix) { close(fd); return; }

    while ((line = get_next_line(fd)) && i < data->height && *line)
    {
        if (i == 0) data->width = ft_wdcounter(line, ' ');
        data->matrix[i] = ft_calloc(sizeof(int), data->width);
        fill_matrix(data->matrix[i], line);
        free(line);
        i++;
    }
    close(fd);
}


// int get_width(char *filename)
// {
//     int width;
//     int fd;
//     char *line;

//     fd = open(filename, O_RDONLY, 0);
//     if (fd < 0)
//         return(-1);
//     line = get_next_line(fd);
//     width = ft_wdcounter(line, ' ');
//     free(line);
//     close(fd);
//     return(width);
// }


// void read_file(char *filename, fdf *data)
// {
//     int fd;
//     char *line;
//     int i;

//     i = 0;
//     data->height = get_height(filename);
//     data->width = get_width(filename);
//     if (data->height < 0 || data->width < 0)
//         return ;
//     data->matrix = ft_calloc(sizeof(int**), (data->height + 1));
//     if (!data->matrix)
//         return;
//     while(i <= data->height)
//         data->matrix[i++] = ft_calloc(sizeof(int*), (data->width + 1));
//     fd = open(filename, O_RDONLY, 0);
//     if (fd < 0)
//     {
//         free(data);
//         exit(-1);
//     }
//     i = 0;
//     line = get_next_line(fd);
//     while(line && i < data->height)
//     {
//         fill_matrix(data->matrix[i], line);
//         free(line);
//         line = get_next_line(fd);
//         i++;
//     }
//     close(fd);
// }