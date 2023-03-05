/* PATRASCU Ioana-Alexandra - grupa 314CB */

#include <stdio.h>
#include <string.h>
#include "struct.h"
#define NameMAX 51
#define DimComanda 60

int main()
{
    Director *root = (Director *)malloc(sizeof(Director));
    Director *dircrt;
    char *comanda = (char *)malloc(DimComanda * sizeof(char));
    char *p;
    if (root == NULL)
    {
        printf("Eroare malloc!");
        return 0;
    }
    if (comanda == NULL)
    {
        printf("Eroare malloc!");
        free(root);
        return 0;
    }
    root->nume = (char *)malloc(NameMAX * sizeof(char));
    if (root->nume == NULL)
    {
        printf("Eroare malloc!");
        free(root);
        free(comanda);
        return 0;
    }

    /* initializare root */
    strcpy(root->nume, "root");
    root->parinte = NULL;
    root->directories = NULL;
    root->files = NULL;
    root->st = NULL;
    root->dr = NULL;
    size_t size = DimComanda;
    dircrt = root;

    /* determinare comanda data in terminal */
    while (1)
    {
        getline(&comanda, &size, stdin);
        p = strtok(comanda, " \n");

        /*-------TOUCH-------*/
        if (strcmp(p, "touch") == 0)
        {
            p = strtok(NULL, " \n");
            touch(&dircrt, p);
        }

        /*-------MKDIR-------*/
        else if (strcmp(p, "mkdir") == 0)
        {
            p = strtok(NULL, " \n");
            mkdir(&dircrt, p);
        }

        /*-------LS-------*/
        else if (strcmp(p, "ls") == 0)
            ls(dircrt);

        /*-------RM-------*/
        else if (strcmp(p, "rm") == 0)
        {
            p = strtok(NULL, " \n");
            rm(&dircrt->files, p);
        }

        /*-------RMDIR-------*/
        else if (strcmp(p, "rmdir") == 0)
        {
            p = strtok(NULL, " \n");
            rmdir(&(dircrt->directories), p);
        }

        /*-------CD-------*/
        else if (strcmp(p, "cd") == 0)
        {
            p = strtok(NULL, " \n");
            cd(dircrt->directories, &dircrt, p);
        }
        /*-------PWD-------*/
        else if (strcmp(p, "pwd") == 0)
        {
            pwd(dircrt);
            printf("\n");
        }

        /*-------FIND-------*/
        else if (strcmp(p, "find") == 0)
        {
            p = strtok(NULL, " \n");
            int found = 0;
            if (strcmp(p, "-f") == 0)
            {
                p = strtok(NULL, " \n");
                findF(root, p, &found);
                if (found == 0)
                    printf("File %s not found!\n", p);
            }
            else
            {
                p = strtok(NULL, " \n");
                findD(root, p, &found);
                if (found == 0)
                    printf("Directory %s not found!\n", p);
            }
        }

        /*-------QUIT-------*/
        else if (strcmp(p, "quit") == 0)
        {
            /* eliberare memorie */
            free(comanda);
            freeAll(root);
            return 0;
        }
    }
}
