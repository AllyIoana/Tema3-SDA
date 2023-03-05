#include <stdio.h>
#include <string.h>
#include "struct.h"

void pwd(Director *dir)
{
    if (dir->parinte != NULL)
        pwd(dir->parinte);
    printf("/%s", dir->nume);
}

/* pentru cautarea unui fisier in arborele de fisiere */
int searchF(File *files, char *nume)
{
    if (files == NULL)
        return 0;
    if (strcmp(nume, files->nume) == 0)
        return 1;
    if (files->st != NULL && strcmp(nume, files->nume) > 0)
        return searchF(files->st, nume);
    else if (files->dr != NULL && strcmp(nume, files->nume) < 0)
        return searchF(files->dr, nume);
    else
        return 0;
}

void findF(Director *dir, char *nume, int *found)
{
    if (searchF(dir->files, nume) == 1)
    {
        *found = 1;
        printf("File %s found!\n", nume);
        pwd(dir);
        printf("\n");
        return;
    }
    if (dir->dr != NULL)
        findF(dir->dr, nume, found);
    if (dir->st != NULL)
        findF(dir->st, nume, found);
    if (dir->directories != NULL)
        findF(dir->directories, nume, found);
}

/* pentru cautarea unui director in arborele directoarelor */
int searchD(Director *dir, char *nume)
{
    if (dir == NULL)
        return 0;
    if (strcmp(nume, dir->nume) == 0)
        return 1;
    if (dir->st != NULL && strcmp(nume, dir->nume) < 0)
        return searchD(dir->st, nume);
    else if (dir->dr != NULL && strcmp(nume, dir->nume) > 0)
        return searchD(dir->dr, nume);
    else
        return 0;
}

void findD(Director *dir, char *nume, int *found)
{
    if (searchD(dir->directories, nume) == 1)
    {
        *found = 1;
        printf("Directory %s found!\n", nume);
        pwd(dir);
        printf("/%s\n", nume);
        return;
    }
    if (dir->dr != NULL)
        findD(dir->dr, nume, found);
    if (dir->st != NULL)
        findD(dir->st, nume, found);
    if (dir->directories != NULL)
        findD(dir->directories, nume, found);
}
