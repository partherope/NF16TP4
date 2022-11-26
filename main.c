#include <stdio.h>
#include "BaseDeDonee.h"
#include <string.h>
//患者的名字和姓名是malloc的，需要手动释放
//Consultation是链表，一样需要释放
//最后释放树
int main()
{
    Patient *test=NULL;
    Parbre head= test;
    inserer_patient(&head,"GAo","Yuan");
    inserer_patient(&head,"GAen","Wenlong");
    Patient *a= rechercher_node_parent(&head,"GAEN");
	return 0;
}
