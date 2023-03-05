/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"
#define NameMAX 51

/* asemanator touch */
/* cautam fisier care are deja numele de adaugat */
int findFile(File *file, char *numedir)
{
    if (strcmp(file->nume, numedir) == 0)
        return 0;
    if (file->st == NULL)
    {
        if (file->dr == NULL)
            return 1;
        else
            return findFile(file->dr, numedir);
    }
    else
    {
        if (file->dr == NULL)
            return findFile(file->st, numedir);
        else
            return findFile(file->st, numedir) * findFile(file->dr, numedir);
    }
}
void mkdir(Director **director, char *numedir)
{
    Director *dir = *director;

    /* cautam fisier cu acelasi nume */
    if (dir->files != NULL)
        if (findFile(dir->files, numedir) == 0)
        {
            printf("File %s already exists!\n", numedir);
            return;
        }

    /* primul subdirector al directorului dat */
    if (dir->directories == NULL)
    {
        dir->directories = (Director *)malloc(sizeof(Director));
        if (dir->directories == NULL)
        {
            printf("Eroare malloc!");
            return;
        }
        // informatii ale subdirectorului
        dir->directories->nume = (char *)malloc(NameMAX * sizeof(char));
        strcpy(dir->directories->nume, numedir);
        dir->directories->parinte = dir;
        dir->directories->st = dir->directories->dr = NULL;
        dir->directories = dir->directories;
        dir->directories->directories = NULL;
        dir->directories->files = NULL;
        dir->directories = dir->directories;
        return;
    }

    /* cautam locatia necesara a subdirectorului */
    Director *directories = dir->directories;
    while (1)
    {
        /* avem acelasi nume */
        if (strcmp(directories->nume, numedir) == 0)
        {
            printf("Directory %s already exists!\n", numedir);
            return;
        }
        /* cautam locatia in care se potriveste numele */
        if (strcmp(numedir, directories->nume) < 0)
        {
            /* mergem pe ramura din stanga */
            if (directories->st != NULL)
                directories = directories->st;

            /* punem fisierul in stanga si completam informatiile */
            else
            {
                directories->st = (Director *)malloc(sizeof(Director));
                if (directories->st == NULL)
                {
                    printf("Eroare malloc!");
                    return;
                }
                directories->st->dr = directories->st->st = NULL;
                directories->st->parinte = directories->parinte;
                directories->st->nume = (char *)malloc(NameMAX * sizeof(char));
                strcpy(directories->st->nume, numedir);
                directories->st->directories = NULL;
                directories->st->files = NULL;
                return;
            }
        }
        else if (strcmp(numedir, directories->nume) > 0)
        {
            /* mergem pe ramura din dreapta */
            if (directories->dr != NULL)
                directories = directories->dr;

            /* punem fisierul in dreapta si completam informatiile */
            else
            {
                directories->dr = (Director *)malloc(sizeof(Director));
                if (directories->dr == NULL)
                {
                    printf("Eroare malloc!");
                    return;
                }
                directories->dr->dr = directories->dr->st = NULL;
                directories->dr->parinte = directories->parinte;
                directories->dr->nume = (char *)malloc(NameMAX * sizeof(char));
                strcpy(directories->dr->nume, numedir);
                directories->dr->directories = NULL;
                directories->dr->files = NULL;
                return;
            }
        }
    }
}
