#include <stdio.h>

#define MAX_SIZE 10

#define ERROR 1
#define SUCCESS 0

int input_matrix(size_t *size, int matrix[][MAX_SIZE])
{
    printf("Input size: ");
    if (scanf("%zu", size) != 1)
        return ERROR;

    if (*size == 0 || *size > MAX_SIZE)
        return ERROR;

    printf("Input elements:\n");
    for (size_t i = 0; i < *size; i++)
    {
        for (size_t j = 0; j < *size; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERROR;
        }
    }

    return SUCCESS;
}

void print_m(int matrix[][MAX_SIZE], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%5d ", matrix[i][j]);  // фикс: %5d
        }
        printf("\n");
    }
}

/* Верхний «треугольник» — максимум */
int obr_1_tr(int matrix[][MAX_SIZE], size_t size)
{
    if (size < 2)
        return matrix[0][0];

    size_t left = 1, right = size - 1;
    size_t vert_mid = size / 2;
    int maxim = matrix[0][1];

    for (size_t row = 0; row < vert_mid; row++)
    {
        for (size_t col = left; col < right; col++)
        {
            if (matrix[row][col] > maxim)
                maxim = matrix[row][col];
        }

        left++;
        right--;
    }

    return maxim;
}

/* Правый «треугольник» — минимум */
int obr_2_tr(int matrix[][MAX_SIZE], size_t size)
{
    if (size < 2)
        return matrix[0][0];

    size_t gor_mid = size / 2;
    size_t left = size - 1;
    size_t right = size - 1;

    int minim = matrix[1][size - 1];

    for (size_t row = 1; row < size - 1; row++)
    {
        for (size_t col = left; col <= right; col++)
        {
            if (matrix[row][col] < minim)
                minim = matrix[row][col];
        }

        if (row < gor_mid)
            left--;
        else
            left++;
    }

    return minim;
}

/* Нижний «треугольник» — сумма чётных */
int obr_3_tr(int matrix[][MAX_SIZE], size_t size)
{
    if (size < 2)
        return 0;

    size_t left = 1, right = size - 1;
    size_t vert_mid = size / 2;
    int summ = 0;

    for (size_t row = size - 1; row > vert_mid; row--)
    {
        for (size_t col = left; col < right; col++)
        {
            if (matrix[row][col] % 2 == 0)
                summ += matrix[row][col];
        }

        left++;
        right--;
    }

    return summ;
}

/* Левый «треугольник» — произведение нечётных */
int obr_4_tr(int matrix[][MAX_SIZE], size_t size)
{
    if (size < 2)
        return 1;

    size_t gor_mid = size / 2;
    size_t left = 0, right = 0;
    int mult = 1;

    for (size_t row = 1; row < size - 1; row++)
    {
        for (size_t col = left; col <= right; col++)
        {
            if (matrix[row][col] % 2 != 0)   // учитываем и отрицательные нечётные
                mult *= matrix[row][col];
        }

        if (row < gor_mid)
            right++;
        else
            right--;
    }

    return mult;
}

int main(void)
{
    int matrix[MAX_SIZE][MAX_SIZE];
    int max, min, summ, mult;
    size_t size;
    int rc;

    rc = input_matrix(&size, matrix);
    if (rc != SUCCESS)
        return rc;

    print_m(matrix, size);

    max = obr_1_tr(matrix, size);
    min = obr_2_tr(matrix, size);
    summ = obr_3_tr(matrix, size);
    mult = obr_4_tr(matrix, size);

    printf("\n%d %d %d %d\n", max, min, summ, mult);

    return SUCCESS;
}