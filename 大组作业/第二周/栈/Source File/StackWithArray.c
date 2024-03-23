#include "StackWithArray.h"

struct Array
{
	int m_Capacity;	//数组的容量
	int m_Top;	//指向栈顶
	int* m_Array;	//栈
};

inline bool a_IsEmpty(Array* stack)	//判断栈区是否为空
{
	return stack->m_Top == EmptyTOS;
}

inline bool a_IsFull(Array* stack)	//判断栈区是否满
{
	return stack->m_Top + 1 == stack->m_Capacity;
}

Array* a_CreateStack(int num)	//创建栈
{
	Array* stack = (Array*)malloc(sizeof(Array));
	if (stack == NULL) {
		return NULL;
	}
	stack->m_Array = (int*)malloc(sizeof(int) * num);
	if (stack == NULL) {
		return NULL;
	}
	stack->m_Capacity = num;
	stack->m_Top = EmptyTOS;
	return stack;
}

void a_MakeEmpty(Array* stack)	//清空栈区，弹出所有元素
{
	assert(stack);
	stack->m_Top = EmptyTOS;
}

Array* a_DisposeStack(Array* stack)	//删除整个栈区
{
	assert(stack);
	free(stack->m_Array);
	stack->m_Array = NULL;
	free(stack);
	stack = NULL;
	return stack;
}

void a_Push(int data, Array* stack)	//元素进栈
{
	if (a_IsFull(stack)) {
		return;
	}
	else {
		stack->m_Array[++stack->m_Top] = data;
	}
}

void a_Pop(Array* stack)	//元素出栈
{
	if (a_IsEmpty(stack)) {
		return;
	}
	else {
		stack->m_Top--;
	}
}

int a_Top(Array* stack)	//返回栈顶元素
{
	assert(!a_IsEmpty(stack));
	return stack->m_Array[stack->m_Top];
}

int a_TopAndPop(Array* stack)	//返回栈顶元素并弹出
{
	assert(!a_IsEmpty(stack));
	return stack->m_Array[stack->m_Top--];
}