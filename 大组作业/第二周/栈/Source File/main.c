#include "StackWithLinkedList.h"
#include "StackWithArray.h"
#include <stdio.h>
#include "Detection.h"
#include "PostfixNotation.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))

int main()
{
	//测试
	const char* infix6 = "10-(80+50) * 7 +4/2";
	printf("%d\n", PostfixNotation(infix6));
	const char* infix5 = "10-80+50";
	printf("%d\n", PostfixNotation(infix5));
	const char* infix1 = "10+80+60";
	printf("%d\n", PostfixNotation(infix1));
	const char* infix2 = "12 + 2 * 3 + ( 3 * 4 + 14 ) * 4";
	printf("%d\n", PostfixNotation(infix2));
	const char* infix4 = "60*(12+34)/2";
	printf("%d\n", PostfixNotation(infix4));
	//const char* infix3 = "(45+98])";	//异常退出
	//printf("%d\n", PostfixNotation(infix3));

	return 0;
}

//int main()
//{
//	Detection("[{(CLANNAD)]AIR");	//栈的平衡符号应用
//}

//int main()
//{
//	Array* stack = a_CreateStack(10);
//	a_IsEmpty(stack);
//	for (int i = 0; i < 10; i++) {
//		a_Push(i, stack);
//	}
//	a_IsFull(stack);
//	a_Pop(stack);
//	a_Pop(stack);
//	printf("%d", a_TopAndPop(stack));
//	printf("%d", a_Top(stack));
//	a_MakeEmpty(stack);
//	stack = a_DisposeStack(stack);
//	
//	return 0;
//}

//int main()
//{
//	Node* stack = l_CreateStack();
//	l_IsEmpty(stack);
//	l_Push(4, stack);
//	l_Push(5, stack);
//	l_Push(6, stack);
//	l_Push(7, stack);
//	l_IsEmpty(stack);
//	l_Pop(stack);
//	l_Top(stack);
//	l_MakeEmpty(stack);
//	l_Push(4, stack);
//	l_Push(5, stack);
//	stack = l_DisposeStack(stack);
//
//	return 0;
//}