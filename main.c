#include <stdio.h>
#include "BaseDeDonee.h"
#include <string.h>
//���ߵ����ֺ�������malloc�ģ���Ҫ�ֶ��ͷ�
//Consultation������һ����Ҫ�ͷ�
//����ͷ���
int main()
{
    Patient *test=NULL,*test2=NULL;
    Parbre head= test,head2=test2;
    int input,niv;
    char nm[20]={0},pr[20]={0},date[20]={0},motif[300]={0};

//    char nm[20]="chen",pr[20]="wenlong",date[20]="3/3",motif[300]={0};
//    char * a=nm;
//    printf("a:%s\n",a);
//    char b[20]={0};
//    strcpy(b,a);
//    printf("b:%s\n",b);
//    gets(nm);
//    printf("a:%s\n",a);
//    printf("b:%s\n",b);
//    gets(motif);
//    printf("%s",motif);
//    inserer_patient(&head,nm,pr);
//    printf("11");
//    ajouter_consultation(&head,nm,date,motif,3);
//    char datee[20]="1/2";
//    ajouter_consultation(&head,nm,datee,motif,4);
//    afficher_fiche(&head,nm);

    while(1){
        printf("1. Ajouter un patient\n"
               "2. Ajouter une consultation �� un patient\n"
               "3. Afficher une fiche m��dicale\n"
               "4. Afficher la liste des patients\n"
               "5. Supprimer un patient\n"
               "6. Copier ou mettre �� jour la liste des patients\n"
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
                printf("Entrez le data et niveau de urgence:\n");
                scanf("%s %d",date,&niv);
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
