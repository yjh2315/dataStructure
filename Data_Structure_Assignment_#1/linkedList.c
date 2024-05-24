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

// 처음으로 삽입되는 노드의 경우 해당 주소를 *linkedList에 넣습니다.
void initList(linkedList **list, int in)
{
	linkedList *new = (linkedList *)malloc(sizeof(linkedList));
	new->data = in;
	new->next = NULL;

	(*list) = new;
}

void newList(linkedList **list, int in, int *length)
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
	(*length)++;
	// linkedList의 길이를 늘린다.
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

// 값을 linkedList에서 삭제시키는 과정이며, n은 0부터 몇번째 위치의 노드를 지울 것인지를 의미합니다.
void delList(linkedList **list, int n, int *length)
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
		(*length)--;
		// linkedList의 길이를 줄인다.
	}
	else
	{
		temp = searchList(list, n - 1);
		linkedList *temp2 = temp->next;
		temp->next = temp->next->next;
		free(temp2);
		(*length)--;
		// linkedList의 길이를 줄인다.
	}
}

// n번째 위치에 새로운 노드를 추가합니다.
void insertList(linkedList **list, int n, int value, int *length)
{
	linkedList *temp;
	linkedList *new = (linkedList *)malloc(sizeof(linkedList));
	new->data = value;
	if (n == 0)
	{
		temp = *list;
		new->next = temp;
		(*list) = new;
		(*length)++;
		// linkedList의 길이를 늘린다.
	}
	else
	{
		temp = searchList(list, n - 1);
		new->next = temp->next;
		temp->next = new;
		(*length)++;
		// linkedList의 길이를 늘린다.
	}
}

int main()
{
	// linkedList의 시작점을 알려주는 포인터입니다.
	linkedList *startNode = NULL;
	// linkedList의 길이를 알려주는 변수입니다.
	int *length;
	(*length) = 0;
	//------------------------------------------------//
	//				1. 구현부

	// 반복횟수를 설정해주는 변수입니다.(노드의 개수)
	// int rep = 10;
	// initList(&startNode, 0);
	// (*length)++;
	// for (int i = 1; i < rep; i++)
	// {
	// 	newList(&startNode, i, length);
	// }
	//
	// // 입력 예시
	// insertList(&startNode, 0, 100, length);
	// printList(startNode);
	// printf("\n");
	// // 0번째 자리
	// insertList(&startNode, 3, 100, length);
	// printList(startNode);
	// printf("\n");
	// // 3번째 자리
	// insertList(&startNode, (*length), 100, length);
	// printList(startNode);
	// printf("\n");
	// // 맨 마지막 자리

	// // 삭제 예시
	// delList(&startNode, 0, length);
	// printList(startNode);
	// printf("\n");
	// // 0번째 자리
	// delList(&startNode, 2, length);
	// printList(startNode);
	// printf("\n");
	// // 2번째 자리
	// delList(&startNode, (*length) - 1, length);
	// printList(startNode);
	// printf("\n\n");
	// // 맨 마지막 자리 (*length)-1.

	// linkedList *specificNode = searchList(&startNode, 4);
	// // specificNode를 설정하고, 해당 노드는 startNode(linkedList)의 0,1,2,3,4 (5번째) 노드를 탐색하는 과정입니다.
	// printf("%d", specificNode->data);
	// // 확인을 위해 값 출력
	//------------------------------------------------//

	//				2. 시간 복잡도 분석, 공간 복잡도 분석

	clock_t start, end;
	double res;

	int rep = 10;
	start = clock();
	initList(&startNode, 0);
	(*length)++;
	for (int i = 1; i < rep; i++)
	{
		insertList(&startNode, 0, 100, length);
	}
	end = clock();
	// start = clock();
	// for (int i = 1; i < rep; i++)
	// {
	// 	linkedList *specificNode = searchList(&startNode, 90);
	// }

	// end = clock();
	res = (double)(end - start) / CLOCKS_PER_SEC;
	printf("LK %d size: 삽입시간 : %f", rep, res);
}