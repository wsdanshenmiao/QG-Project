//用栈实现后缀表达式的计算和中缀表达式转换成后缀表达式,只能算整数
#include "PostfixNotation.h"


int ConvertCharToInt(char* position, int* const pi)	//将字符串转换为数字
{
	int ret = 0;
	char ch = *position;
	while ('0' <= ch && ch <= '9') {
		ret = ret * 10 + ch - '0';
		position++;
		ch = *position;
		(*pi)++;
	}
	return ret;
}

//operator1比operator2高或相等返回true
bool Priority(char operator1, char operator2)	//判断两个符号优先级
{
	switch (operator1) {
	case '(':
	case ')':
		return true;
	case '*':
	case '/':
		if (operator2 == '(' || operator2 == ')') {
			return false;
		}
		else {
			return true;
		}
	case '+':
	case '-':	//同级别时在前的优先级高
		//if (operator2 == '+' || operator2 == '-') {
		//	return true;
		//}
		return false;
	}
	printf("error in label");
	exit(EXIT_FAILURE);
}

void Calculate(const char operator, Node* const calculateStack)
{
	int num1 = l_TopAndPop(calculateStack);
	int num2 = l_TopAndPop(calculateStack);
	switch (operator) {
	case '+':
		l_Push(num2 + num1, calculateStack);
		break;
	case '-':
		l_Push(num2 - num1, calculateStack);
		break;
	case '*':
		l_Push(num2 * num1, calculateStack);
		break;
	case '/':
		l_Push(num2 / num1, calculateStack);
		break;
	}
}

int PostfixNotation(const char* infix)
{
	Node* convertStack = l_CreateStack();	//用来转换的栈
	Node* calculateStack = l_CreateStack();	//用来计算结果的栈
	int i = 0;
	for (char ch = *(infix + i); ch != '\0'; i++, ch = *(infix + i)) {
		if (ch == ' ') {	//除去空格
			continue;
		}
		else if ('0' <= ch && ch <= '9') {	//若为数字
			//将整个字符转换为数字,并入计算栈
			l_Push(ConvertCharToInt(infix + i, &i) , calculateStack);
			i--;	//函数内已经包括了跳过的字符数，这里减去整个循环多加的一次
		}
		else if (ch == ')') {
			while (!l_IsEmpty(convertStack) && l_Top(convertStack) != '(') {
				Calculate(l_TopAndPop(convertStack), calculateStack);	//弹出操作符并计算
			}
			if (l_IsEmpty(convertStack)) {	//若为空则没有'('，输入符号错误，异常退出
				printf("error in label");
				exit(EXIT_FAILURE);

			}
			else {	//若前面有'('，弹出并正常进行
				l_Pop(convertStack);
			}
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(') {	//若为运算符号
			if (l_IsEmpty(convertStack)) {
				l_Push(ch, convertStack);
			}
			else if (Priority(ch, l_Top(convertStack))) {	//若栈顶优先级低，入栈
				l_Push(ch, convertStack);
			}
			else {	//反之弹出后再入栈计算
				//注意这里要先判断是否为空，否则会先进行返回栈顶操作，若为空就会报错
				while (!l_IsEmpty(convertStack) && l_Top(convertStack) != '(') {
					Calculate(l_TopAndPop(convertStack), calculateStack);
				}
				l_Push(ch, convertStack);
			}
		}
		else {
			printf("error in label");
			exit(EXIT_FAILURE);
		}
	}
	while (!l_IsEmpty(convertStack)) {	//将所有符号弹出
		Calculate(l_TopAndPop(convertStack), calculateStack);
	}
	int ret = calculateStack->m_Next->m_Data;	//返回计算栈中最后的结果
	convertStack = l_DisposeStack(convertStack);
	calculateStack = l_DisposeStack(calculateStack);
	return ret;
}