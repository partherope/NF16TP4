#include <stdio.h>
#include "BaseDeDonee.h"
#include <string.h>
//���ߵ����ֺ�������malloc�ģ���Ҫ�ֶ��ͷ�
//Consultation������һ����Ҫ�ͷ�
//����ͷ���
int main()
{
    Patient *test=NULL;
    Parbre head= test;
    inserer_patient(&head,"GAo","Yuan");
    inserer_patient(&head,"GAen","Wenlong");
    Patient *a= rechercher_node_parent(&head,"GAEN");
	return 0;
}
