#ifndef __POSIFIXNOTATION__H__
#define __POSIFIXNOTATION__H__

#include "StackWithLinkedList.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

int ConvertCharToInt(char* position, int* pi);	//将字符串转换为数字
bool Priority(char operator1, char operator2);	//判断两个符号优先级
void Calculate(const char operator, Node* const calculateStack);
int PostfixNotation(const char* infix);


#endif // 

