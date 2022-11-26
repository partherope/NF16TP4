#ifndef NF16TP4_BASEDEDONEE_H
#define NF16TP4_BASEDEDONEE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Consultation
{
    char *date;//JJ-MM-AAAA
    char *motif;
    int niveauUrg;
    struct Consultation *suivant;
}Consultation;

typedef struct Patient
{
    char *nom;
    char *prenom;
    Consultation *ListeConsult;
    int nbrconsult;// le nombre de consultations du patient

    struct Patient *fils_gauche;
    struct Patient *fils_droit;
}Patient;
typedef Patient *Parbre;


char *strupr(char *str);
int comparer(char * a, char *b);//a>b 1;a<b 0;a=b -1
void supprimerConsltation(Consultation *Liste);//une fonction recursive pour liberer la memoire de Consultation
Patient * rechercher_node_parent(Parbre * abr, char* nm);
Patient *CreerPatient(char *nm,char *pr);
void inserer_patient(Parbre * abr, char * nm, char * pr);
Patient * rechercher_patient(Parbre * abr, char* nm);
void afficher_fiche(Parbre * abr, char* nm);
void afficher_patients(Parbre * abr);
Consultation * CreerConsult(char * date, char* motif, int nivu);
void ajouter_consultation(Parbre * abr, char * nm, char * date, char* motif, int nivu);
void supprimer_patient(Parbre * abr, char* nm);
void maj(Parbre * abr, Parbre * abr2);

#endif
