#include "fdf.h"

int	print_err(char *msg)
{
	ft_printf("%s", msg);
	return (1);
}

int	mem_err(int fd, char *msg)
{
	ft_printf("%s", msg);
	close(fd);
	return (1);
}

int	err_and_close(int fd)
{
	close(fd);
	return (1);
}

int	err_free(char *line, char *msg)
{
	ft_printf("%s", msg);
	free(line);
	return (1);
}

int err_free_arr(void	free_array(char**), char **array, char *msg)
{
	ft_printf("%s", msg);
	free_array(array);
	return (1);
}