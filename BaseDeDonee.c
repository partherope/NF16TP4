#include "BaseDeDonee.h"
Patient *CreerPatient(char *nm,char *pr)
{
    Patient *NewPatient=(Patient *)malloc(sizeof(Patient));
    NewPatient->nom=nm;
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
