#ifndef __STACKWITHARRAY__H__
#define __STACKWITHARRAY__H__

#define EmptyTOS (-1)

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Array Array;
inline bool a_IsEmpty(Array* stack);	//判断栈区是否为空
inline bool a_IsFull(Array* stack);	//判断栈区是否满
Array* a_CreateStack(int num);	//创建栈
void a_MakeEmpty(Array* stack);	//清空栈区，弹出所有元素
Array* a_DisposeStack(Array* stack);	//删除整个栈区
void a_Push(int data, Array* stack);	//元素进栈
void a_Pop(Array* stack);	//元素出栈
int a_Top(Array* stack);	//返回栈顶元素
int a_TopAndPop(Array* stack);	//返回栈顶元素并弹出

#endif // !__STACKWITHARRAY__H__
