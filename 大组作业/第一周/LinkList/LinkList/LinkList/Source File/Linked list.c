#include "Linked list.h"


/*
	Return value:
		链表为空时返回true
	Parameter:
		list:链表的头指针
*/
bool IsEmpty(const Node* const list)	//判断链表是否为空
{
	return list->m_Next == NULL;
}

/*
	Return value:
		为最后一个节点时返回true
	Parameter:
		position:需要判断的节点的指针
*/
bool IsLast(const Node* const position)	//判断该节点是否为最后一个节点
{
	return position->m_Next == NULL;
}

/*
	Return value:
		返回查找元素的位置
	Parameter:
		data:需要查找的数据
		list:链表的头指针
*/
Node* Find(const int data, const Node* list)	//查找某个元素
{
	Node* position;
	for (position = list->m_Next; position != NULL && position->m_Data!= data; position=position->m_Next);
	return position;
}

/* 
	Return value:
		  返回指向前驱元的指针
	Parameter:
		data:要查找的元素
		list：链表
*/
Node* FindPrevious(const int data, Node* const list)	//查找某个元素的前驱元
{
	Node* position = list;
	for (; position->m_Next != NULL && position->m_Next->m_Data != data; position = position->m_Next);
	return position;
}

/*
	Return value:
		无返回值
	Parameter:
		data:要删除的元素
		list:链表的头指针
*/
void Delete(const int data, Node* const list)	//删除某个元素
{
	Node* previous = FindPrevious(data, list);
	if (!IsLast(previous)) {
		Node* tmp = previous->m_Next;
		previous->m_Next = tmp->m_Next;
		free(tmp);
	}
}

/*
	Return value:
		无返回值
	 Parameter:
		data:要添加的元素
		position:元素添加在position之后
*/
void Insert(const int data, Node* position)	//插入某个元素
{
	assert(position);
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		return;
	}
	tmp->m_Data = data;
	tmp->m_Next = position->m_Next;
	position->m_Next = tmp;
}

/*
	Return value:
		返回某个节点中的数据
	Parameter:
		position:要查询的节点
*/
int Retrieve(Node* position)	//查询节点中的数据
{

	return position->m_Data;
}

/*
	Return value:
		返回删除数据后的链表头指针
	Parameter:
		list:要删除数据的链表
*/
Node* MakeEmpty(Node* const list)	//清空链表
{
	Node* position = list->m_Next;
	list->m_Next = NULL;
	while (position) {
		Node* tmp = position->m_Next;
		free(position);
		position = tmp;
	}
	return list;
}

/*
	Return value:
		返回空指针
	Parameter:
		list:要删除的链表
*/
Node* DeleteList(Node* list)	//删除整个链表
{
	while (list) {
		Node* tmp = list->m_Next;
		free(list);
		list = tmp;
	}
	return list;
}