#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_POINT 3
#define MAX_SIZE 10

#define ERROR 1
#define SUCCESS 0

typedef struct
{
    char name[MAX_NAME_POINT];
    int x;
    int y;
} points;

float distance(points p1, points p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

float area(points p1, points p2, points p3)
{
    float a = distance(p1, p2);
    float b = distance(p2, p3);
    float c = distance(p3, p1);

    float p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int input(points *point)
{
    if (fgets(point->name, MAX_NAME_POINT, stdin) == NULL)
        return ERROR;

    size_t len = strlen(point->name);
    if (len > 0 && point->name[len - 1] == '\n')
        point->name[len - 1] = '\0';

    if (scanf("%d %d", &point->x, &point->y) != 2)
        return ERROR;

    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    return SUCCESS;
}

int main(void)
{
    points points_arr[MAX_SIZE];
    size_t count_points;

    if (scanf("%zu", &count_points) != 1 || count_points <= 0 || count_points > MAX_SIZE)
        return ERROR;

    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    for (size_t i = 0; i < count_points; i++)
    {
        input(&points_arr[i]);
    }

    float max_area = -1;
    points p_m1;
    points p_m2;
    points p_m3;

    for (size_t i = 0; i < count_points; i++)
    {
        for (size_t j = 0; j < count_points; j++)
        {
            for (size_t k = 0; k < count_points; k++)
            {
                if (max_area < area(points_arr[i], points_arr[j], points_arr[k]))
                {
                    max_area = area(points_arr[i], points_arr[j], points_arr[k]);
                    p_m1 = points_arr[i];
                    p_m2 = points_arr[j];
                    p_m3 = points_arr[k];
                }
            }
        }
    }

    printf("\nMax area: %f\n", max_area);
    printf("Point1: %s - %d %d, Point2: %s - %d %d, Point3: %s - %d %d\n", p_m1.name, p_m1.x, p_m1.y, p_m2.name, p_m2.x, p_m2.y, p_m3.name, p_m3.x, p_m3.y);
        
    return SUCCESS;
}
