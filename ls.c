/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"
#define NameMAX 51

void DRSfiles(File *file)
{
    if (file->dr != NULL)
        DRSfiles(file->dr);
    printf("%s ", file->nume);
    if (file->st != NULL)
        DRSfiles(file->st);
}

void SRDdir(Director *dir)
{
    if (dir->st != NULL)
        SRDdir(dir->st);
    printf("%s ", dir->nume);
    if (dir->dr != NULL)
        SRDdir(dir->dr);
}

void ls(Director *dir)
{
    if (dir->directories != NULL)
        SRDdir(dir->directories);
    if (dir->files != NULL)
        DRSfiles(dir->files);
    printf("\n");
}
