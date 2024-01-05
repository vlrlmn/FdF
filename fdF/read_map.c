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

int read_and_fill(int fd, fdf *data)
{
    char *line;
    int i;

    i = 0;
    while ((line = get_next_line(fd)) && i < data->height && *line)
    {
        if (i == 0) 
            data->width = ft_wdcounter(line, ' ');
        data->matrix[i] = ft_calloc(sizeof(int), data->width);
        fill_matrix(data->matrix[i], line);
        free(line);
        i++;
    }
    return((i == data->height));
}

int read_file(char *filename, fdf *data)
{
    int fd;
    char *line;
    int i;
    int result;
    
    i = 0;

    fd = open(filename, O_RDONLY, 0);
    if (fd < 0) 
        return (1);
    data->height = get_height(filename);
    data->matrix = ft_calloc(sizeof(int*), data->height);
    if (!data->matrix)
    { 
        close(fd); 
        return(1); 
    }
    result = read_and_fill(fd, data);
    close(fd);
    return(0);
}
