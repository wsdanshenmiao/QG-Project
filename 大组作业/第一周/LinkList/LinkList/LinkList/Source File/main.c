#include "Linked list.h"
#include <stdlib.h>

#define MALLOC(T) ((T*)malloc(sizeof(T)))

int main()
{
	Node* list = MALLOC(Node);
	list->m_Next = NULL;
	IsEmpty(list);
	IsLast(list);
	Insert(3, list);
	Insert(4, Find(3, list));
	Find(3, list);
	Retrieve(list->m_Next);
	Delete(3, list);
	list = MakeEmpty(list);
	Insert(1, list);
	list = DeleteList(list);

	return 0;
}