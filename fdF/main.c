#include "fdf.h"


int main(int argc, char **argv)
{
    if (!argv[1] || argc != 2)
        exit(EXIT_FAILURE);

    fdf *data;
    data = (fdf*)malloc(sizeof(fdf));
    if (!data)
        exit(EXIT_FAILURE);
    else if (read_file(argv[1], data))
    {
        free(data);
        exit(EXIT_FAILURE);
    }
    int i, j;

    // Печать матрицы
    i = 0;
    while(i < data->height)
    {
        j = 0;
        while(j < data->width)
        {
            printf("%3d", data->matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    // Освобождение памяти
    for (i = 0; i < data->height; i++) {
        free(data->matrix[i]);  // Освобождение вложенных массивов
    }
    free(data->matrix);         // Освобождение главного массива
    free(data);

    return 0;
}

// int main(int argc, char **argv)
// {
//     if (!argv[1] || argc != 2)
//         exit(EXIT_FAILURE);
//     fdf *data;
//     data = (fdf*)malloc(sizeof(fdf));
//     if (!data)
//         exit(EXIT_FAILURE);
//     else
//         read_file(argv[1], data);

//     int i;
//     int j;

//     i = 0;
//     while(i < data->height)
//     {
//         j = 0;
//         while(j < data->width)
//         {
//             printf("%3d", data->matrix[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
//     free(data->matrix);
//     free(data);
// }

    // if(2 == argc && ft_strncmp(argv[1], "name", 5) || 4 == argc && !ft_strncmp(argv[1], "name", 5))
    // {
    //     //prompt correct
        
    // }
    // else
    //     putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
    //     exit(EXIT_FAILURE);