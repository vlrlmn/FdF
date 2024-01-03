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

    for (i = 0; i < data->height; i++) {
        free(data->matrix[i]);  
    }
    free(data->matrix);
    free(data);
    return 0;
}
