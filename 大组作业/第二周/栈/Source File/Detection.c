//用栈实现平衡符号的检测
#include "StackWithLinkedList.h"
#include "Detection.h"

bool Detection(const char* pc)	//用栈实现平衡符号的检测,若正确返回true，错误返回false
{
	assert(pc);
	char* ch = pc;
	Node* stack = l_CreateStack();
	for (; *ch != '\0'; ch++) {
		switch (*ch) {
		case '[':
		case '{':
		case '(':
			l_Push(*ch, stack);	//开放符号时入栈
			break;
		case ']':
		case '}':
			//封闭符号则当栈空时报错；否则，将栈元素弹出。若不是对应的开放符号，报错
			if (l_IsEmpty(stack)|| l_TopAndPop(stack) + 2 != *ch) {
				l_DisposeStack(stack);
				return false;
			}
			break;
		case ')':
			if (l_IsEmpty(stack) || l_TopAndPop(stack) + 1 != *ch) {
				l_DisposeStack(stack);
				return false;
			}
			break;
		}
	}
	if (l_IsEmpty(stack)) {	//在文件尾，如果栈非空则报错。
		l_DisposeStack(stack);
		return true;
	}
	else {
		l_DisposeStack(stack);
		return false;
	}
}
