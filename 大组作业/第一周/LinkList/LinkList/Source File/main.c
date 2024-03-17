#define _CRT_SECURE_NO_WARNINGS

#include "Linked list.h"
#include <stdlib.h>

#define MALLOC(T) ((T*)malloc(sizeof(T)))

enum Function
{
	EXIT,
	PRINTLIST,
	RETRIEVE,
	DELETE,
	INSERT,
	MAKEEMPTY,
	PARITYSWITCH,
	FINDMID,
	REVERSAL
};

void Catalogue()
{
	printf("***************************0.EXIT			1.PRINTLIST************************\n");
	printf("***************************2.RETRIEVE			3.DELETE***************************\n");
	printf("***************************4.INSERT			5.MAKEEMPTY************************\n");
	printf("***************************6.PARITYSWITCH		7.FINDMID**************************\n");
	printf("***************************		8.REVERSAL		***************************\n");

}

int main()
{
	enum Function select;
	Node* list = MALLOC(Node);
	list->m_Next = NULL;
	for (int i = 0; i < 3; i++) {
		Insert(i, list);
	}
	do {
		Catalogue();	//打印目录
		printf("请选择:");
		scanf("%d", &select);
		getchar();
		system("cls");
		switch (select)
		{
		case EXIT:
			DeleteList(list);
			break;
		case PRINTLIST: {
			PrintList(list);
			getchar();
			break;
		}
		case RETRIEVE: {
			int data;
			PrintList(list);
			printf("输入要检索的对象：");
			scanf("%d", &data);
			Node* node = Find(data, list);
			if (node) {
				printf("%d\n", Retrieve(node));
			}
			else {
				printf("无此对象：");
			}
			getchar();
			getchar();
			break;
		}
		case DELETE: {
			int data;
			PrintList(list);
			printf("请输入要删除的数据：");
			scanf("%d", &data);
			Node* node = Find(data, list);
			if (node) {
				Delete(data, list);
				printf("删除成功。\n");
			}
			else {
				printf("无此对象：");
			}
			getchar();
			getchar();
			break;
		}
		case INSERT: {
			int data;
			printf("请输入要插入的数据：");
			scanf("%d", &data);
			Insert(data, list);
			printf("插入成功。\n");
			getchar();
			break;
		}
		case MAKEEMPTY: {
			MakeEmpty(list);
			printf("删除成功。\n");
			getchar();
			break;
		}
		case PARITYSWITCH: {
			ParitySwitch(list);
			printf("交换成功。\n");
			getchar();
			break;
		}
		case FINDMID: {
			Node* mid = FindMid(list);
			if (mid) {
				printf("%d\n", Retrieve(mid));
			}
			else {
				printf("无中间元素");
			}
			getchar();
			break;
		}
		case REVERSAL: {
			list = Reversal(list);
			printf("反转成功。\n");
			getchar();
			break;
		}		
		default: {
			printf("输入错误。\n");
			getchar();
			break;
		}
		}
		system("cls");
	} while (select);

	return 0;
}