/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"
#define NameMAX 51

/* vedem daca exista un director cu numele fisierului de adaugat */
/* daca gasim unul, afisam eroarea */
int findDir(Director *dir, char *numefis)
{
    if (strcmp(dir->nume, numefis) == 0)
        return 0;
    if (dir->st == NULL)
    {
        if (dir->dr == NULL)
            return 1;
        else
            return findDir(dir->dr, numefis);
    }
    else
    {
        if (dir->dr == NULL)
            return findDir(dir->st, numefis);
        else
            return findDir(dir->st, numefis) * findDir(dir->dr, numefis);
    }
}

void touch(Director **director, char *numefis)
{
    Director *dir = *director;

    /* cautam director cu acelasi nume */
    if (dir->directories != NULL)
        if (findDir(dir->directories, numefis) == 0)
        {
            printf("Directory %s already exists!\n", numefis);
            return;
        }

    /* primul fisier al directorului dat */
    if (dir->files == NULL)
    {
        File *files = (File *)malloc(sizeof(File));
        if (files == NULL)
        {
            printf("Eroare malloc!");
            return;
        }

        // informatii ale fisierului
        files->nume = (char *)malloc(NameMAX * sizeof(char));
        strcpy(files->nume, numefis);
        files->parinte = dir;
        files->st = files->dr = NULL;
        dir->files = files;
        return;
    }

    /* cautam locatia necesara a fisierului */
    File *files = dir->files;
    while (1)
    {
        if (strcmp(files->nume, numefis) == 0) //avem acelasi nume
        {
            printf("File %s already exists!\n", numefis);
            return;
        }
        /* cautam locatia in care se potriveste numele */
        if (strcmp(numefis, files->nume) < 0)
        {
            /* mergem pe ramura din dreapta */
            if (files->dr != NULL)
                files = files->dr;
            /* punem fisierul in dreapta si completam informatiile */
            else
            {
                files->dr = (File *)malloc(sizeof(File));
                if (files->dr == NULL)
                {
                    printf("Eroare malloc!");
                    return;
                }
                files->dr->dr = files->dr->st = NULL;
                files->dr->parinte = files->parinte;
                files->dr->nume = (char *)malloc(NameMAX * sizeof(char));
                strcpy(files->dr->nume, numefis);
                return;
            }
        }
        else if (strcmp(numefis, files->nume) > 0)
        {
            /* mergem pe ramura din stanga */
            if (files->st != NULL)
                files = files->st;
            /* punem fisierul in stanga si completam informatiile */
            else
            {
                files->st = (File *)malloc(sizeof(File));
                if (files->st == NULL)
                {
                    printf("Eroare malloc!");
                    return;
                }
                files->st->dr = files->st->st = NULL;
                files->st->parinte = files->parinte;
                files->st->nume = (char *)malloc(NameMAX * sizeof(char));
                strcpy(files->st->nume, numefis);
                return;
            }
        }
    }
}
