/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"

void freeFiles(File *file)
{
    if (file == NULL)
        return;
    if (file->dr != NULL)
        freeFiles(file->dr);
    if (file->st != NULL)
        freeFiles(file->st);
    free(file->nume);
    free(file);
}

void freeDirectories(Director *dir)
{
    if (dir == NULL)
        return;
    if (dir->dr != NULL)
        freeDirectories(dir->dr);
    if (dir->st != NULL)
        freeDirectories(dir->st);
    freeFiles(dir->files);
    free(dir->nume);
    free(dir);
}

void freeAll(Director *director)
{
    freeFiles(director->files);
    freeDirectories(director->directories);
    free(director->nume);
    free(director);
}
