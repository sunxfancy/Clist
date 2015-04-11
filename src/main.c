/* 
* @Author: sxf
* @Date:   2015-04-11 13:21:44
* @Last Modified by:   sxf
* @Last Modified time: 2015-04-11 19:49:00
*/

#include <stdio.h>
#include <malloc.h>
#include "list.h"

LIST_DEF(Int_List)
	int data;
LIST_DEF_END(Int_List)

Int_List* Create_Int_List(int k) {
	MALLOC(Int_List, obj);
	obj->data = k;
	LIST_CREATE_INIT(obj);
	return obj;
}

list* l;

int main() {
	l = Create_List();
	list_add(l, (list_node*)Create_Int_List(3));
	list_add(l, (list_node*)Create_Int_List(8));
	list_add(l, (list_node*)Create_Int_List(5));

	list_for_each(Int_List* , i, l) {
		printf("%d\n", i->data);
	} for_each_end	
	
    return 0;
}