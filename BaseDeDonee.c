#include "BaseDeDonee.h"
#include <string.h>
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

Patient * rechercher_node_parent(Parbre * abr, char* nm)//寻找目标结点的父节点
{
    Patient *temp=(*abr);
    Patient *Parent=NULL;
    while(temp!=NULL)
    {
        if(comparer(temp->nom,nm)==1)
        {
            Parent=temp;
            temp=temp->fils_gauche;
        }
        else if(comparer(temp->nom,nm)==0)
        {
            Parent=temp;
            temp=temp->fils_droit;
        }
        else if(comparer(temp->nom,nm)==-1)
            return Parent;
    }
    return NULL;
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
    printf("创建完成");
    return NewPatient;
}

void inserer_patient(Parbre *abr, char *nm,char *pr)
{
    if((*abr)==NULL)
    {
        (*abr) = CreerPatient(nm,pr);
    }//l'arbre est vide où on arrive à notre noeud cible
    else if(comparer((*abr)->nom,nm)==1)
    {
        inserer_patient(&((*abr)->fils_gauche),nm,pr);
    }

    else if(comparer((*abr)->nom,nm)==0)
        inserer_patient(&(*abr)->fils_droit,nm,pr);
    else if(comparer((*abr)->nom,nm)==-1)
        printf("Failure! Le patient %s existe",nm);
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
    Patient *CiblePatient= rechercher_patient(abr,nm);
    if(!CiblePatient)
    {
        printf("On trouve pas le patient %s",nm);
        exit(EXIT_FAILURE);
    }
    Consultation *temp=CiblePatient->ListeConsult;
    for(;temp->suivant!=NULL;temp=temp->suivant);
    temp->suivant= CreerConsult(date,motif,nivu);
    CiblePatient->nbrconsult++;
}

//void supprimer_patient(Parbre * abr, char* nm)
//{
//    Patient *target= rechercher_patient(abr,nm);
//    if(target->fils_droit==NULL && target->fils_gauche==NULL)
//    {
//        supprimerConsltation(target->ListeConsult);
//        free(target);
//    }
//}