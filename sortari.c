#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER 40
typedef struct{
    float price;
    char title[MAX_NUMBER];
    char genre[MAX_NUMBER];
    char author_name[MAX_NUMBER];
    int stock;
    int stars;

}Book;


int compar_alfabetic_titlu(void const *a, void const *b)
{
    Book *p1 = (Book *)a;
    Book *p2 = (Book *)b;
    return strcmp(p1->title, p2->title);
}

int compar_pretc(void const *a, void const *b)
{
    int p1 = ((Book *)a)->price;
    int p2 = ((Book *)b)->price;
    return p1 - p2;
}

int compar_pretd(void const *a, void const *b)
{
    int p1 = ((Book *)a)->price;
    int p2 = ((Book *)b)->price;
    return p2 - p1;
}
int compar_rating(void const *a, void const *b)
{
    int p1 = ((Book *)a)->stars;
    int p2 = ((Book *)b)->stars;
    return p2 - p1;
}

int compar_stock(void const *a, void const *b)
{
    int p1 = ((Book *)a)->stock;
    int p2 = ((Book *)b)->stock;
    return p2 - p1;
}