#include "BaseDeDonee.h"
#include <string.h>
char* MajusculeString(char *a)
{
    char *returnvalue= malloc((strlen(a)+1)* sizeof(char));
    int i=0;
    while(*(a+i)!='\0')
    {

        if(*(a+i)>='a' && *(a+i)<='z')
            returnvalue[i]=*(a+i)-32;
        else
            returnvalue[i]=*(a+i);
        i++;
    }
    returnvalue[i]='\0';
    return returnvalue;
}

int comparer(char * a, char *b){
    int i=0;
    while(i<strlen(a) || i<strlen(b)){
        if(*(a+i) > *(b+i)) return 1;
        else if (*(a+i) < *(b+i)) return 0;
        else if (*(a+i) == *(b+i)) i++;
    }
    if (strlen(a) > strlen(b)) return 1;//la situation comme a[aaab],b[aaa]
    else if (strlen(a) < strlen(b)) return 0;
    else return -1;//si les 2 chaine sont les meme.
}
Patient *search_the_rightmost_of_lefttree(Parbre abr)
{
    if(abr==NULL)//�ų�һ��ʼ���ǿյ��������ֹ����
        return NULL;
    Patient *Return=abr;
    if(abr->fils_gauche==NULL)//���������������
        return Return;
    else
        Return=Return->fils_gauche;
    while(Return->fils_droit!=NULL)//����ֱ��������Ϊ��
    {
        Return=Return->fils_droit;
    }
    return Return;
}

void supprimerConsltation(Consultation *Liste)
{
    if(Liste!=NULL){
    if(Liste->suivant!=NULL)
        supprimerConsltation(Liste->suivant);
        free(Liste->date);
        free(Liste->motif);
    }
    free(Liste);
}

Patient * rechercher_node_parent(Parbre * abr, char* nm)//Ѱ��Ŀ����ĸ��ڵ�,�������޸��ڵ㣬�򷵻��䱾��
{
    Patient *temp=(*abr);
    Patient *Parent=temp;
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
    NewPatient->nom = MajusculeString(nm);
    NewPatient->prenom=MajusculeString(pr);
    NewPatient->nbrconsult=0;
    NewPatient->fils_droit=NewPatient->fils_gauche=NULL;
    NewPatient->ListeConsult=NULL;
    return NewPatient;
}

void inserer_patient(Parbre *abr, char *nm,char *pr)
{
    char *temp=NULL;
    temp= MajusculeString(nm);
    if((*abr)==NULL)
    {

        (*abr) = CreerPatient(nm,pr);
    }//l'arbre est vide o�� on arrive �� notre noeud cible
    else if(comparer((*abr)->nom, temp)==1)
    {

        inserer_patient(&((*abr)->fils_gauche),nm,pr);
    }

    else if(comparer((*abr)->nom,nm)==0)
    {
        inserer_patient(&(*abr)->fils_droit,nm,pr);
    }

    else if(comparer((*abr)->nom,nm)==-1)
    {
        printf("Failure! Le patient %s existe",nm);
        free(temp);
    }

}

Patient * rechercher_patient(Parbre * abr, char* nm)
{
    Patient *temp=(*abr);
    nm = MajusculeString(nm);
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
    free(nm);
    return NULL;
}

void afficher_fiche(Parbre * abr, char* nm)
{
    nm= MajusculeString(nm);
    Patient *cible= rechercher_patient(abr,nm);
    if(!cible)
    {
//        printf("Pas de patient %s",nm); //��rechercher�������Ѿ�����ʾ��
        return;
    }
    printf("Informations de le/la patient:\n",nm);
    printf("Nom:%s, Pr��nom:%s, numbre de consultations:%d\n",cible->nom,cible->prenom, cible->nbrconsult);
    for(Consultation *temp=cible->ListeConsult;temp!=NULL;temp=temp->suivant)
    {
        printf("Date:%s | Motif:%s | Niveau urgent:%d\n",temp->date,temp->motif,temp->niveauUrg);
    }
    putchar('\n');
}

void afficher_patients(Parbre * abr)
{
    if(*abr)
    {
        printf("Nom: %s | Pr��nom: %s\n",(*abr)->nom,(*abr)->prenom);
        afficher_patients(&(*abr)->fils_gauche);
        afficher_patients(&(*abr)->fils_droit);
    }
}

Consultation * CreerConsult(char * date, char* motif, int nivu)
{

    Consultation *NewCons=(Consultation *)malloc(sizeof(Consultation));
    if(!NewCons)
    {
        printf("Malloc Error!");
        exit(EXIT_FAILURE);
    }
    NewCons->date= malloc(sizeof(char));
    NewCons->motif= malloc(sizeof(char));
    strcpy(NewCons->date,date);
    strcpy(NewCons->motif,motif);
    NewCons->niveauUrg=nivu;
    NewCons->suivant=NULL;
    return NewCons;
}

void ajouter_consultation(Parbre * abr, char * nm, char * date, char* motif, int nivu)
{
    Patient *CiblePatient= rechercher_patient(abr,nm);
    if(!CiblePatient)
    {
//        printf("On trouve pas le patient %s",nm);
//        exit(EXIT_FAILURE);
        return;
    }
    else{
        Consultation *temp=CiblePatient->ListeConsult;
        if(temp!=NULL) {
            for(;temp->suivant!=NULL;temp=temp->suivant);
            temp->suivant= CreerConsult(date,motif,nivu);
        }
        else if(temp==NULL) CiblePatient->ListeConsult= CreerConsult(date,motif,nivu);
        CiblePatient->nbrconsult++;
    }
}

void supprimer_patient(Parbre * abr, char* nm)
{
    nm= MajusculeString(nm);
    Patient *target= rechercher_patient(abr,nm);
    if(target==NULL)
        return;
    if(target->fils_droit==NULL && target->fils_gauche==NULL)//������������
    {
        Patient *Parent= rechercher_node_parent(abr,nm);
        if(Parent==target)//ɾ���Ľ�������Ǹ����
            (*abr)=NULL;
        else if(Parent->fils_gauche==target)//��ɾ���Ľ������������
            Parent->fils_gauche=NULL;
        else if(Parent->fils_droit==target)//��ɾ���Ľ������������
            Parent->fils_droit=NULL;
        supprimerConsltation(target->ListeConsult);
        free(target->nom);
        free(target->prenom);
        free(target);
    }
    else if(target->fils_droit==NULL && target->fils_gauche!=NULL)//�������գ��������ǿ�
    {
        Patient *Parent=rechercher_node_parent(abr,nm);
        if(Parent==target)//ɾ���Ľ�������Ǹ����
        {
            (*abr)=target->fils_gauche;
            supprimerConsltation(target->ListeConsult);
            free(target->nom);
            free(target->prenom);
            free(target);
            return;
        }
        if(comparer(Parent->nom,target->nom)==1)
        {
            Parent->fils_gauche=target->fils_gauche;
        }
        else if(comparer(Parent->nom,target->nom)==0)
        {
            Parent->fils_droit=target->fils_gauche;
        }
        supprimerConsltation(target->ListeConsult);
        free(target->nom);
        free(target->prenom);
        free(target);
    }
    else if(target->fils_droit!=NULL && target->fils_gauche==NULL)//�������գ��������ǿ�
    {
        Patient *Parent=rechercher_node_parent(abr,nm);
        if(Parent==target)//ɾ���Ľ�������Ǹ����
        {
            (*abr)=target->fils_droit;
            supprimerConsltation(target->ListeConsult);
            free(target->nom);
            free(target->prenom);
            free(target);
            return;
        }
        if(comparer(Parent->nom,target->nom)==1)
        {
            Parent->fils_gauche=target->fils_droit;
        }
        else if(comparer(Parent->nom,target->nom)==0)
        {
            Parent->fils_droit=target->fils_droit;
        }
        supprimerConsltation(target->ListeConsult);
        free(target->nom);
        free(target->prenom);
        free(target);
    }
    else if(target->fils_droit!=NULL && target->fils_gauche!=NULL){
    //������������Ϊ�գ�������ѡ�������������ҵĽ����Ϊ�滻���
    Patient *replace= search_the_rightmost_of_lefttree(target);
    if(!replace){
        printf("Arbre Nul!");
        return;
    }
    Patient *ParentOfTarget= rechercher_node_parent(abr,target->nom);//
    Patient *ParentOfReplace= rechercher_node_parent(abr,replace->nom);
    //Ŀ��ڵ��Ǹ��������
    if(ParentOfTarget==target)
    {
        if(ParentOfReplace==ParentOfTarget)//����������պ�����
        {
            if(ParentOfReplace->fils_droit==replace)
                ParentOfReplace->fils_droit=replace->fils_gauche;
            else if(ParentOfReplace->fils_gauche==replace)
                ParentOfReplace->fils_gauche=replace->fils_gauche;
        }
        if(replace->fils_gauche==NULL)//�滻�ڵ�û������
        {
            replace->fils_gauche=target->fils_gauche;
            replace->fils_droit=target->fils_droit;
            (*abr)=replace;
        }
        else if(replace->fils_gauche)
        {
            if(ParentOfReplace->fils_droit==replace)
                ParentOfReplace->fils_droit=replace->fils_gauche;
            else if(ParentOfReplace->fils_gauche==replace)
                ParentOfReplace->fils_gauche=replace->fils_gauche;
            replace->fils_gauche=target->fils_gauche;
            replace->fils_droit=target->fils_droit;
            (*abr)=replace;
        }
    }
    else//��ɾ����㲻�Ǹ����
    {
        //���Ƿֳ�2�������һ���滻���������������һ��û��
        if(replace->fils_gauche==NULL)//��������
        {
            if(ParentOfTarget->fils_gauche==target)
                ParentOfTarget->fils_gauche=replace;
            else if(ParentOfTarget->fils_droit=target)
                ParentOfTarget->fils_droit=replace;
            if(ParentOfReplace->fils_gauche==replace)
                ParentOfReplace->fils_gauche=NULL;
            else if(ParentOfReplace->fils_droit==replace)
                ParentOfReplace->fils_droit=NULL;
            replace->fils_gauche=target->fils_gauche;
            replace->fils_droit=target->fils_droit;
        }
        else if(replace->fils_gauche!=NULL)//�������������
        {
            if(ParentOfReplace->fils_gauche==replace)
                ParentOfReplace->fils_gauche=replace->fils_gauche;
            else if(ParentOfReplace->fils_droit==replace)
                ParentOfReplace->fils_droit=replace->fils_gauche;

            if(ParentOfTarget->fils_gauche==target)
                ParentOfTarget->fils_gauche=replace;
            else if(ParentOfTarget->fils_droit==target)
                ParentOfTarget->fils_droit=replace;

            replace->fils_gauche=target->fils_gauche;
            replace->fils_droit=target->fils_droit;
        }
    }
    supprimerConsltation(target->ListeConsult);
    free(target->nom);
    free(target->prenom);
    free(target);
    }
}

void maj(Parbre * abr, Parbre * abr2){
    if(*abr) {
        inserer_patient(abr2, (*abr)->nom, (*abr)->prenom);
        Consultation * temp=(*abr)->ListeConsult;
        if(temp!=NULL) {
            for (;temp!=NULL;temp=temp->suivant) {
                ajouter_consultation(abr2, (*abr)->nom, temp->date, temp->motif,temp->niveauUrg);
            }
        }
        maj(&(*abr)->fils_gauche, abr2);
        maj(&(*abr)->fils_droit, abr2);
    }
};

void des(Parbre *abr){
    if(*abr!=NULL) {
        des(&(*abr)->fils_gauche);
        des(&(*abr)->fils_droit);
        supprimerConsltation((*abr)->ListeConsult);
        free((*abr)->nom);
        free((*abr)->prenom);
        free((*abr));
    }
}

//Parbre * zhong(Parbre *abr){
//    if((*abr)->fils_gauche!=NULL){
//        zhong(&(*abr)->fils_gauche);
//    }
//    else return abr;
//}
