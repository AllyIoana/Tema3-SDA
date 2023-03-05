/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"
#define NameMAX 51

void rm(File **fis, char *numefis)
{
    File *files = *fis;
    File *rmfileParent = NULL;
    File *rmfile = NULL;

    /* arborele de fisier gol */
    if (files == NULL)
    {
        printf("File %s doesn't exist!\n", numefis);
        return;
    }

    /* cautam fisierul */
    while (rmfile == NULL)
    {
        if (strcmp(files->nume, numefis) == 0)
            rmfile = files;
        else if (strcmp(numefis, files->nume) > 0 && files->st != NULL)
        {
            rmfileParent = files;
            files = files->st;
        }
        else if (strcmp(numefis, files->nume) < 0 && files->dr != NULL)
        {
            rmfileParent = files;
            files = files->dr;
        }
        else
        {
            printf("File %s doesn't exist!\n", numefis);
            return;
        }
    }

    /* daca fisierul e frunza */
    if (rmfile->st == NULL && rmfile->dr == NULL)
    {
        // fara legatura de la parinte
        if (rmfileParent != NULL)
            if (strcmp(rmfileParent->nume, rmfile->nume) > 0)
                rmfileParent->dr = NULL;
            else
                rmfileParent->st = NULL;
        else
            *fis = NULL;

        // eliberare
        free(rmfile->nume);
        free(rmfile);
        return;
    }

    /* fisierul are doar fiul din dreapta */
    if (rmfile->st == NULL && rmfile->dr != NULL)
    {
        // restabilim o legatura intre parintele fisierului si fiul din dreapta
        if (rmfileParent != NULL)
            if (strcmp(rmfileParent->nume, rmfile->nume) > 0)
                rmfileParent->dr = rmfile->dr;
            else
                rmfileParent->st = rmfile->dr;
        else
            *fis = rmfile->dr;

        //eliberam memoria
        free(rmfile->nume);
        free(rmfile);
        return;
    }

    /* fisierul are doar fiul din stanga */
    if (rmfile->dr == NULL && rmfile->st != NULL)
    {
        // restabilim o legatura intre parintele fisierului si fiul din stanga
        if (rmfileParent != NULL)
            if (strcmp(rmfileParent->nume, rmfile->nume) > 0)
                rmfileParent->dr = rmfile->st;
            else
                rmfileParent->st = rmfile->st;
        else
            *fis = rmfile->st;

        //eliberam memoria
        free(rmfile->nume);
        free(rmfile);
        return;
    }

    /* fisierul are 2 fii: caz final */
    /* cautam cea mai mica valoare a subarborelui din stanga */
    /* (cea mai din dreapta) */
    /* eliminam valoarea gasita prin aceeasi functie */
    /* refolosim variabila files */
    files = rmfile->st;
    while (files->dr != NULL)
        files = files->dr;
    strcpy(rmfile->nume, files->nume);
    rm(&rmfile->st, files->nume);
}
