#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BaseDeDonee.h"
int main()
{
    Parbre head=CreerPatient("GAO","Yuan");
//    inserer_patient(&head,"GAO","Yuan");
    printf("%d", comparer((*head).nom,"GAO"));
	return 0;
}
