#define _CRT_SERCURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct linkedList *pLinkedList;
// LinkedList의 포인터를 pLinkedList로 선언하여 linkedList 선언부에 사용했습니다.

typedef struct linkedList
{
	int data;
	pLinkedList next;
} linkedList;
// linkedList를 int형의 data를 가지고, 다음 linkedList의 주소(포인터)를 갖는 구조체를 선언했습니다.

void newList(linkedList **list, int in)
{
	// doublePointer형식의 linkedList가 들어오면 새로 linkedList노드를 만들어 기존 linkedList에 연결합니다.
	linkedList *new = (linkedList *)malloc(sizeof(linkedList));
	new->data = in;
	new->next = NULL;

	// 첫 노드가 아닐 경우 노드들의 끝을 찾아야 하기에 변수를 새로 설정하고, 계속 next로 마지막 값을 찾으며 마지막에서 주소를 전달합니다.
	pLinkedList temp = *list;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

void initList(linkedList **list, int in)
{
	linkedList *new = (linkedList *)malloc(sizeof(linkedList));
	new->data = in;
	new->next = NULL;

	(*list) = new;
}

// linkedList의 데이터를 출력하기 위한 함수입니다.
void printList(linkedList *list)
{
	while (list != NULL)
	{
		printf("%d\n", list->data);
		list = list->next;
	}
}

// linkedList에서 n번째 노드를 탐색하는 메소드입니다.
linkedList *searchList(linkedList **list, int n)
{
	if (list == NULL)
	{
		return NULL;
	}
	else
	{
		linkedList *temp = *list;
		for (int i = 0; i < n; i++)
		{
			if (temp == NULL)
			{
				return NULL;
			}
			else
			{
				temp = temp->next;
			}
		}
		return temp;
	}
}

// // n은 0번째 위치부터 몇번째 위치의 노드를 지울 것인지를 의미합니다.
// void delList(linkedList **list, int n)
// {
// 	linkedList **temp = list;
// 	if (temp == NULL)
// 	{
// 		printf("삭제할 리스트가 없습니다.");
// 		return;
// 	}
// 	if (n == 0)
// 	{
// 		linkedList *temp2 = (*temp);
// 		*list = (*temp)->next;
// 		linkedList *temp3 = (*temp);
// 		free(temp2);
// 	}
// 	else
// 	{
// 		temp = searchList(list, n - 1);
// 		linkedList *temp2 = (*temp)->next;
// 		(*temp)->next = (*temp)->next->next;
// 		free(temp2);
// 	}
// }

// n은 0번째 위치부터 몇번째 위치의 노드를 지울 것인지를 의미합니다.
void delList(linkedList **list, int n)
{
	linkedList *temp = *list;
	if (temp == NULL)
	{
		printf("삭제할 리스트가 없습니다.");
		return;
	}
	if (n == 0)
	{
		linkedList *temp2 = temp;
		*list = temp->next;
		free(temp);
	}
	else
	{
		temp = searchList(list, n - 1);
		linkedList *temp2 = temp->next;
		temp->next = temp->next->next;
		free(temp2);
	}
}

void insertList(linkedList **list, int n, int value)
{
	linkedList *temp;
	linkedList *new = (linkedList *)malloc(sizeof(linkedList));
	new->data = value;

	if (n == 0)
	{
		temp = list;
		new->next = temp;
		(*list) = new;
	}
	else
	{
		temp = searchList(list, n - 1);
		new->next = temp->next;
		temp->next = new;
	}
}

int main()
{
	// linkedList의 시작점을 알려주는 포인터입니다.
	linkedList *startNode = NULL;

	// random을 통해 rep개의 데이터를 무작위로 삽입할 예정입니다. 이를 통해 O(n)을 계산할 수 있습니다.
	int rep = 11;
	initList(&startNode, 0);
	for (int i = 1; i < rep; i++)
	{
		newList(&startNode, i);
	}
	delList(&startNode, 0);
	insertList(&startNode, 10, 100);

	printList(startNode);
}