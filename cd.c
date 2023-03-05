/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"

void cd(Director *director, Director **dircautat, char *nume)
{
    /* pentru intoarcerea la directorul-parinte */
    if (strcmp(nume, "..") == 0)
    {
        if ((*dircautat)->parinte == NULL)
            return;
        *dircautat = (*dircautat)->parinte;
        return;
    }

    /* mutarea in alt director */
    while (1)
    {
        if (director == NULL)
        {
            printf("Directory not found!\n");
            return;
        }
        if (strcmp(nume, director->nume) == 0)
        {
            *dircautat = director;
            return;
        }
        if (strcmp(nume, director->nume) > 0)
            director = director->dr;
        else if (strcmp(nume, director->nume) < 0)
            director = director->st;
        else
        {
            printf("Directory not found!\n");
            return;
        }
    }
}
