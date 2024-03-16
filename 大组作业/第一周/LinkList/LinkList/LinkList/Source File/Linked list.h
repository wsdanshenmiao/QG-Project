#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node	//链表的定义
{
	int m_Data;
	struct Node* m_Next;
}Node;

bool IsEmpty(const Node* const list);	//判断链表是否为空
bool IsLast(const Node* const position);	//判断该节点是否为最后一个节点
Node* Find(const int data, const Node* list);	//查找某个元素
void Delete(const int data, Node* const list);	//删除某个元素
void Insert(const int data, Node* position);	//插入某个元素
int Retrieve(Node* position);	//查询节点中的数据
Node* MakeEmpty(Node* const list);	//清空链表
Node* DeleteList(Node* list);	//删除整个链表