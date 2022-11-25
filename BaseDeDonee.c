#include "BaseDeDonee.h"
#include <string.h>

char *strupr(char *str)
{
char *ptr = str;

while (*ptr != '\0') {
if ((*ptr)<=122&&(*ptr)>=97)
*ptr = (*ptr)-32;
ptr++;
}

return str;
}

Patient *CreerPatient(char *nm,char *pr)
{
    Patient *NewPatient=(Patient *)malloc(sizeof(Patient));
    NewPatient->nom=strupr(nm);
    NewPatient->prenom=pr;
    return NewPatient;
}

void inserer_patient(Parbre *abr, char *nm,char *pr)
{
    if(abr==NULL)
    {
        Patient *NewNode=(Patient *)malloc(sizeof(Patient));
        if(!NewNode)
        {
            printf("Malloc Error!");
            exit(EXIT_FAILURE);
        }
        NewNode->nom=nm;
        NewNode->prenom=pr;
        NewNode->nbrconsult=0;
        NewNode->fils_droit=NewNode->fils_gauche=NULL;
        NewNode->ListeConsult=NULL;
        *abr=NewNode;
    }//l'arbre est vide où on arrive à notre noeud cible
    else if((*abr)->nom[0]>nm[0])
        inserer_patient(&(*abr)->fils_gauche,nm,pr);
    else if((*abr)->nom[0]>nm[0])
        inserer_patient(&(*abr)->fils_droit,nm,pr);
}

int comparer(char * a, char *b){
    int i=0;
    while(1){
        if(*(a+i) > *(b+i)) return 1;
        else if (*(a+i) < *(b+i)) return 0;
        else if (*(a+i) == *(b+i)) i++;
    }
}
