/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <stdlib.h>

/* pentru a folosi dependenta , le declaram inainte */
typedef struct dir Director;
typedef struct file File;

/* structura pentru fisiere - ordonate lexicografic */
struct file
{
    char *nume; /* numele fisierului */
    Director *parinte; /* pointer catre directorul parinte */
    struct file *st; /* pointer catre fisierul din stanga */
    struct file *dr; /* pointer catre fisierul din dreapta */ 
};

/* structura pentru directoare */
struct dir
{
    char *nume; /* nume director */
    struct dir *parinte; /* pointer catre directorul parinte */
    File *files; /* pointer catre radacina arborelui de fisiere */
    struct dir *directories; /* pointer catre radacina arborelui de subdirectoare */
    struct dir *st; /* pointer catre directorul din stanga */
    struct dir *dr; /* pointer catre directorul din dreapta */
};

void touch(Director **director, char *numefis);
void mkdir(Director **director, char *numedir);
void ls(Director *dir);
void rm(File **file, char* numefis);
void rmdir(Director **director, char* numedir);
void cd(Director *dir, Director **dircautat, char *nume);
void pwd(Director *dir);

/* functii de cautare */
void findF(Director *dir, char *nume, int *found);
void findD(Director *dir, char *nume, int *found);

/* functii de eliberare de memorie */
void freeFiles(File *file);
void freeDirectories(Director *dir);
void freeAll(Director *director);
