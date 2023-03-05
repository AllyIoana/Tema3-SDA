/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"

void rmdir(Director **director, char *numedir)
{
    Director *dir = *director;
    Director *rmdirParent = NULL;
    Director *rmDir = NULL;

    /* arborele de directoare gol */
    if (dir == NULL)
    {
        printf("Directory %s doesn't exist!\n", numedir);
        return;
    }

    /* cautam directorul */
    while (rmDir == NULL)
    {
        if (strcmp(dir->nume, numedir) == 0)
            rmDir = dir;
        else if (strcmp(numedir, dir->nume) > 0 && dir->dr != NULL)
        {
            rmdirParent = dir;
            dir = dir->dr;
        }
        else if (strcmp(numedir, dir->nume) < 0 && dir->st != NULL)
        {
            rmdirParent = dir;
            dir = dir->st;
        }
        else
        {
            printf("Directory %s doesn't exist!\n", numedir);
            return;
        }
    }

    /* daca directorul e frunza */
    if (rmDir->st == NULL && rmDir->dr == NULL)
    {
        // fara legatura de la parinte
        if (rmdirParent != NULL) // nu e radacina
            if (strcmp(rmdirParent->nume, rmDir->nume) > 0)
                rmdirParent->st = NULL;
            else
                rmdirParent->dr = NULL;
        else
            (*director) = NULL;

        // eliberare
        freeFiles(rmDir->files);
        freeDirectories(rmDir->directories);
        free(rmDir->nume);
        free(rmDir);
        return;
    }

    /* directorul are doar fiul din dreapta */
    if (rmDir->st == NULL && rmDir->dr != NULL)
    {
        // restabilim o legatura intre parintele fisierului si fiul din dreapta
        if (rmdirParent != NULL) // nu e radacina
            if (strcmp(rmdirParent->nume, rmDir->nume) < 0)
                rmdirParent->dr = rmDir->dr;
            else
                rmdirParent->st = rmDir->dr;
        else
            (*director) = rmDir->dr;

        //eliberam memoria
        freeFiles(rmDir->files);
        freeDirectories(rmDir->directories);
        free(rmDir->nume);
        free(rmDir);
        return;
    }

    /* directorul are doar fiul din stanga */
    if (rmDir->dr == NULL && rmDir->st != NULL)
    {
        // restabilim o legatura intre parintele directoruluisi fiul din stanga
        if (rmdirParent != NULL) // nu e radacina
            if (strcmp(rmdirParent->nume, rmDir->nume) < 0)
                rmdirParent->dr = rmDir->st;
            else
                rmdirParent->st = rmDir->st;
        else
            (*director) = rmDir->st;

        //eliberam memoria
        freeFiles(rmDir->files);
        freeDirectories(rmDir->directories);
        free(rmDir->nume);
        free(rmDir);
        return;
    }

    /* directorul are 2 fii: caz final */
    /* cautam cea mai mica valoare a subarborelui din stanga (cea mai din dreapta) */
    /* eliminam valoarea gasita prin aceeasi functie */
    /* refolosim variabila dir */
    dir = rmDir->st;
    while (dir->dr != NULL)
        dir = dir->dr;
    strcpy(rmDir->nume, dir->nume);
    rmdir(&(rmDir->st), dir->nume);
}
