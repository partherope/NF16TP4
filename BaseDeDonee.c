#include "BaseDeDonee.h"
#include <string.h>

char *strupr(char *str)
{
char *ptr = str;

while (*ptr != '\0') {
if ((*ptr)<=122&&(*ptr)>=97)
*ptr = *ptr-32;
ptr++;
}

return str;
}

int comparer(char * a, char *b){
    int i=0;
    while(i<strlen(a) || i<strlen(a)){
        if(*(a+i) > *(b+i)) return 1;
        else if (*(a+i) < *(b+i)) return 0;
        else if (*(a+i) == *(b+i)) i++;
    }
    if (strlen(a) > strlen(b)) return 1;//la situation comme a[aaab],b[aaa]
    else if (strlen(a) < strlen(b)) return 0;
    else return -1;//si les 2 chaine sont les meme.
}

void supprimerConsltation(Consultation *Liste)
{
    if(Liste->suivant!=NULL)
        supprimerConsltation(Liste->suivant);
    free(Liste);
}

Patient *CreerPatient(char *nm,char *pr)
{
    Patient *NewPatient=(Patient *)malloc(sizeof(Patient));
    if(!NewPatient)
    {
        printf("Malloc Error!");
        exit(EXIT_FAILURE);
    }
    NewPatient->nom=strupr(nm);
    NewPatient->prenom=pr;
    NewPatient->nbrconsult=0;
    NewPatient->fils_droit=NewPatient->fils_gauche=NULL;
    NewPatient->ListeConsult=NULL;
    return NewPatient;
}

void inserer_patient(Parbre *abr, char *nm,char *pr)
{
    if(abr==NULL)
    {
        *abr= CreerPatient(nm,pr);
    }//l'arbre est vide où on arrive à notre noeud cible
    else if(comparer((*abr)->nom,nm))
        inserer_patient(&(*abr)->fils_gauche,nm,pr);
    else if(comparer((*abr)->nom,nm)==0)
        inserer_patient(&(*abr)->fils_droit,nm,pr);
}

Patient * rechercher_patient(Parbre * abr, char* nm)
{
    Patient *temp=(*abr);
    while(temp!=NULL)
    {
        if(comparer(temp->nom,nm)==1)
            temp=temp->fils_gauche;
        else if(comparer(temp->nom,nm)==0)
            temp=temp->fils_droit;
        else if(comparer(temp->nom,nm)==-1)
            return temp;
    }
    printf("Il n'y pas de patient %s!\n",nm);
    return NULL;
}

void afficher_fiche(Parbre * abr, char* nm)
{
    Patient *cible= rechercher_patient(abr,nm);
    if(!cible)
    {
        printf("Pas de patient %s",nm);
        return;
    }
    printf("Informations de le/la patient:\n",nm);
    printf("Nom:%s, Prénom:%s, numbre de consultations:%d",cible->nom,cible->prenom, cible->nbrconsult);
    printf("Le/la patient(e) a eu %d consultations",cible->nbrconsult);
    for(Consultation *temp=cible->ListeConsult;temp!=NULL;temp=temp->suivant)
    {
        printf("Date:%s | Motif:%s | Niveau urgent:%d\n",temp->date,temp->motif,temp->niveauUrg);
    }
    putchar('\n');
}

void afficher_patients(Parbre * abr)
{
    if(abr)
    {
        printf("Nom: %s | Prénom: %s",(*abr)->nom,(*abr)->prenom);
        afficher_patients(&(*abr)->fils_gauche);
        afficher_patients(&(*abr)->fils_droit);
    }
}

Consultation * CreerConsult(char * date, char* motif, int nivu)
{
    Consultation *NewCons=(Consultation *) malloc(sizeof(Consultation));
    if(!NewCons)
    {
        printf("Malloc Error!");
        exit(EXIT_FAILURE);
    }
    NewCons->date=date;
    NewCons->motif=motif;
    NewCons->niveauUrg=nivu;
    return NewCons;
}

void ajouter_consultation(Parbre * abr, char * nm, char * date, char* motif, int nivu)
{
    Patient *CilbePatient= rechercher_patient(abr,nm);
    if(!CilbePatient)
    {
        printf("On trouve pas le patient %s",nm);
        exit(EXIT_FAILURE);
    }
    Consultation *temp=CilbePatient->ListeConsult;
    for(;temp->suivant!=NULL;temp=temp->suivant);
    temp->suivant= CreerConsult(date,motif,nivu);
}

void supprimer_patient(Parbre * abr, char* nm)
{

}