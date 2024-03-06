#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "func.h"
#define MAX_NUMBER 40

typedef struct{
    float price;
    char title[MAX_NUMBER];
    char genre[MAX_NUMBER];
    char author_name[MAX_NUMBER];
    int stock;
    int stars;

}Book;



void citire(int n, FILE *f, Book v[])
{
    for(int i=0; i<n; i++)
    {
        fscanf(f, "%f\n", &v[i].price);
        fgets(v[i].title, MAX_NUMBER, f);
        v[i].title[strlen(v[i].title)-1]='\0';
        fgets(v[i].author_name, MAX_NUMBER, f);
        v[i].author_name[strlen(v[i].author_name)-1]='\0';
        fgets(v[i].genre, MAX_NUMBER, f);
        v[i].genre[strlen(v[i].genre)-1]='\0';
        fscanf(f, "%d\n", &v[i].stock);
        fscanf(f, "%d", &v[i].stars);

    }
}

void afisare_autor(int n, Book v[], char w[])
{
    int ok = 0;
    for(int i=0;i<n;i++)
        if(strcmp(v[i].author_name, w)==0)
        {
            ok=1;
            if(v[i].stock!=0)
                printf("%s   %.2f lei  in stoc\n",v[i].title, v[i].price);
            else
                printf("%s   %.2f lei  stoc epuizat\n ",v[i].title, v[i].price);
        }
    if(ok == 0)
        printf("Autorul cautat nu este disponibil\n");
}

void afisare_titlu(int n, Book v[], char w[])
{
    int ok = 0;
    for(int i=0;i<n;i++)
        if(strcmp(v[i].title, w)==0)
        {
            if(v[i].stock!=0)
                printf("%s de %s   %.2f lei  in stoc\n",v[i].title, v[i].author_name ,v[i].price);
            else
                printf("%s de %s   %.2f lei  stoc epuizat\n ",v[i].title, v[i].author_name ,v[i].price);
            ok=1;
        }
    if(ok == 0)
        printf("Cartea cautata nu este disponibila\n");
}

void afisare_pret(int n, Book v[], float x)
{
    for(int i=0;i<n;i++)
        if(v[i].price <= x)
        {
             if(v[i].stock!=0)
                printf("%s de %s   %s  %.2f lei in stoc\n",v[i].title, v[i].author_name ,v[i].genre,v[i].price);
            else
                printf("%s de %s   %s  %.2f lei stoc epuizat\n ",v[i].title, v[i].author_name ,v[i].genre, v[i].price);
        }

}
void afisare_gen(int n, Book v[], char w[])
{
    int ok = 0;
    printf("%s\n",w);
    for(int i=0;i<n;i++)
        if(strcmp(v[i].genre, w)==0)
        {
            if(v[i].stock!=0)
                printf("%s de %s   %.2f lei  in stoc\n",v[i].title, v[i].author_name ,v[i].price);
            else
                printf("%s de %s   %.2f lei  stoc epuizat\n ",v[i].title, v[i].author_name ,v[i].price);
            ok=1;
        }
    if(ok == 0)
        printf("Genul cautat nu este disponibil\n");
}

void afisare_tot(int n, Book v[])
{
    qsort(v,n,sizeof(Book), compar_rating);
    for(int i = 0; i<n ; i++)
    {
        if(v[i].stock !=0 )
        {
            printf("%s    %.2f lei    in stoc   ", v[i].title, v[i].price);
            for(int j=0; j<v[i].stars; j++)
                printf("*");
            printf("\n");
        }
        else
        {
            printf("%s    %.2f lei   stoc epuizat   ", v[i].title, v[i].price);
             for(int j=0; j<v[i].stars; j++)
                printf("*");
            printf("\n");
        }

    }
}


int main()
{
    FILE *f = fopen("depozit.txt", "r");
    FILE *g = fopen("donatii.txt", "a");
    FILE *h = fopen("recenzii.txt", "a");
    FILE *fis = fopen("autorul_lunii.txt", "r");
    FILE *k = fopen("raftul_meu.txt", "w");
    if(g==NULL || f==NULL || h==NULL || fis==NULL || k==NULL)
        {
            printf("Eroare la deschiderea a cel putin unuia dintre fisiere!\n");
            exit(1);
        }
    int capacity,op, nr_stele, numar;
    float buget, cupon;
    char ch,l;
    char *nume =(char *)malloc((MAX_NUMBER + 1)* sizeof(char));
    char *titlu =(char *)malloc((MAX_NUMBER + 1)* sizeof(char));
    char *gen =(char *)malloc((MAX_NUMBER + 1)* sizeof(char));
    char *nume_a_l =(char *)malloc((MAX_NUMBER + 1)* sizeof(char));
    char *nume_carte =(char *)malloc((MAX_NUMBER + 1) * sizeof(char));
    if(nume==NULL || titlu==NULL || gen==NULL || nume_carte==NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        exit(1);
    }
    char mesaj[100];
    fscanf(f, "%d\n", &capacity);
    Book *b = (Book * )malloc(capacity * sizeof(Book));
    if( b==NULL)
    {
        printf("Eroare la alocarea memoriei pentru baza de date\n");
        exit(1);
    }
    
    citire(capacity,f, b );
    afisare_tot(capacity, b);
    printf("-----------------------------------------------\n");
    fgets(nume_a_l, MAX_NUMBER, fis);
    for(int i=0; i<capacity; i++)
        if(strcmp(b[i].author_name, nume_a_l) == 0)
            b[i].price = b[i].price - 0.2*b[i].price;
    printf("Orice carte scrisa de autorul lunii este redusa cu 20 de procente\n");
    printf("Autorul lunii este: %s\n" , nume_a_l);
    srand(time(NULL));
    printf("Tombola in care puteti castiga un cupon de 20 de lei\n");
    printf("Doriti sa participati?(y/n):");
    scanf("%c", &l);
    if(l == 'y')
    {
        int noroc = (rand() % 20) + 1;
        printf("Introduceti un numar de la 1 la 20 : ");
        scanf("%d", &numar);
        if(numar == noroc)
            {
                cupon = 50;
                printf("Felicitari !!! Esti castigator\n");
            }
        else
            {
                printf("Nu ai castigat\n");
                cupon = 0;
            }
    } 
    while(1)
    {
        printf("MENIU\n");
        printf("1.Cumpara carte\n");
        printf("2.Doneaza carte\n");
        printf("3.Scrie o recenzie\n");
        printf("4.Exit\n");
        printf("Optiunea dvs:");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                printf("cauta dupa:\n");
                printf("10.Autor\n");
                printf("11.Titlu\n");
                printf("12.Pret\n");
                printf("13.Gen\n");
                printf("Introduceti 10/11/12/13 in functie de ce vreti sa cautati:");
                scanf("%d", &ch);
            switch (ch)
            {
            case 10:
                printf("Numele autorului : ");
                scanf("\n");
                fgets(nume, MAX_NUMBER, stdin);
                nume[strlen(nume)-1]='\0';
                qsort(b, capacity, sizeof(Book), compar_alfabetic_titlu);
                afisare_autor(capacity, b, nume);
                printf("Numele cartii pe care o doriti: ");
                fgets(nume, MAX_NUMBER, stdin);
                nume[strlen(nume)-1]='\0';
                fprintf(k, "%s\n", nume);
                break;
            case 11:
                printf("Titlu : ");
                scanf("\n");
                fgets(titlu, MAX_NUMBER, stdin);
                titlu[strlen(titlu)-1]='\0';
                afisare_titlu(capacity, b, titlu);
                printf("Numele cartii pe care o doriti: ");
                fgets(nume, MAX_NUMBER, stdin);
                nume[strlen(nume)-1]='\0';
                fprintf(k, "%s\n", nume);
                break;
            case 12:
                printf("Buget disponibil : ");
                scanf("\n");
                scanf("%f", &buget );
                buget = buget + cupon;
                qsort(b,capacity, sizeof(Book), compar_pretc);
                afisare_pret(capacity, b, buget);
                printf("Numele cartii pe care o doriti: ");
                scanf("\n");
                fgets(nume, MAX_NUMBER, stdin);
                nume[strlen(nume)-1]='\0';
                fprintf(k, "%s\n", nume);
                break;
            case 13:
                printf("Gen : ");
                scanf("\n");
                fgets(gen, MAX_NUMBER, stdin);
                gen[strlen(gen)-1]='\0';
                afisare_gen(capacity, b, gen);
                printf("Numele cartii pe care o doriti: ");
                fgets(nume, MAX_NUMBER, stdin);
                nume[strlen(nume)-1]='\0';
                fprintf(k, "%s\n", nume);
                break;
            default:
                printf("Reincercati");
                break;
            }
            break;
            case 2:
                printf("Introduceti detaliile cartii pe care doriti sa o donati\n");
                printf("Numele autorului : ");
                scanf("\n");
                fgets(nume, MAX_NUMBER, stdin);
                nume[strlen(nume)-1]='\0';
                printf("Titlu : ");
                fgets(titlu, MAX_NUMBER, stdin);
                titlu[strlen(titlu)-1]='\0';
                fprintf(g, "%s     %s\n", titlu , nume );
                fseek(g, 1 , SEEK_CUR);
            break;
            case 3:
                printf("Numele cartii : ");
                scanf("\n");
                fgets(nume_carte, MAX_NUMBER, stdin);
                printf("Exprimati-va opinia(maxim 100 de caractere): ");
                fgets(mesaj , 100, stdin);
                mesaj[strlen(mesaj)-1]='\0';
                nume_carte[strlen(nume_carte)-1]='\0';
                fprintf(h, "%s    ",nume_carte);
                printf("introduceti numarul de stele in functie de cat de mult v-a placut cartea(de la 1 la 5):");
                scanf("%d", &nr_stele);
                for(int i=0; i<nr_stele;i++)
                    fprintf(h,"★ ");
                char ghil ='"';
                fprintf(h, "    %c%s%c\n",ghil,mesaj,ghil);
                fprintf(f, "\n");
                fseek(g, 1 , SEEK_CUR);
            break;
            case 4:
            printf("La revedere!\n");
            exit(0);
            break;
            default:
            printf("Reincercati");
        }
    break;
    }
    free(nume_a_l);
    free(nume_carte);
    free(gen);
    free(nume);
    free(titlu);
    free(b);
    fclose(f);
    fclose(g);
    fclose(h);
    fclose(fis);
    return 0;
}
