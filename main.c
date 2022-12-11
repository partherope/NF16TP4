#include <stdio.h>
#include "BaseDeDonee.h"
#include <string.h>

int main()
{
    Patient *test=NULL,*test2=NULL;
    Parbre head= test,head2=test2;
    int input,niv;
    char nm[20]={0},pr[20]={0},date[20]={0},motif[300]={0};

    while(1){
        printf("1. Ajouter un patient\n"
               "2. Ajouter une consultation d'un patient\n"
               "3. Afficher une fiche médicale\n"
               "4. Afficher la liste des patients\n"
               "5. Supprimer un patient\n"
               "6. Copier ou mettre à jour la liste des patients\n"
               "7. Quitter\n");
        printf("Choisissez le fonction :\n");
        scanf("%d",&input);
        switch (input) {
            case 1:
                getchar();
                printf("vous avez choisi ajouter un patient, entrez le prenom et nom :\n");
                scanf("%s %s",pr,nm);
                inserer_patient(&head,nm,pr);
                printf("OK\n");
                break;
            case 2:
                getchar();
                printf("vous avez choisi ajouter une consultation �� un patient, entrez le nom du patient:\n");
                scanf("%s",nm);
                printf("Entrez le data dans forme JJ-MM-AAAA:\n");
                scanf("%s",date);
                getchar();
                printf("Entrez le urgence:\n");
                scanf("%d",&niv);
                getchar();
                printf("Entrez le motif:\n");
                gets(motif);
                ajouter_consultation(&head,nm,date,motif,niv);
                printf("OK\n");
                break;
            case 3:
                getchar();
                printf("vous avez choisi afficher une fiche m��dicale, entrez le nom du patient:\n");
                scanf("%s",nm);
                afficher_fiche(&head,nm);
                printf("OK\n");
                break;
            case 4:
                getchar();
                printf("vous avez choisi afficher la liste des patients\n");
                afficher_patients(&head);
                printf("OK\n");
                break;
            case 5:
                getchar();
                printf("vous avez choisi supprimer un patient, entrez le nom du patient:\n");
                scanf("%s",nm);
                supprimer_patient(&head,nm);
                printf("OK\n");
                break;
            case 6:
                getchar();
                des(&head2);
                head2=NULL;
                maj(&head,&head2);
                afficher_patients(&head2);
                break;
            case 7:
                des(&head);
                return 0;
        }
    }
}
