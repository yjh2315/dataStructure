#define _CRT_SERCURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct linkedList *pLinkedList;
// LinkedList�� �����͸� pLinkedList�� �����Ͽ� linkedList ����ο� ����߽��ϴ�.

typedef struct linkedList
{
	int data;
	pLinkedList next;
} linkedList;
// linkedList�� int���� data�� ������, ���� linkedList�� �ּ�(������)�� ���� ����ü�� �����߽��ϴ�.

void newList(linkedList **list, int in)
{
	// doublePointer������ linkedList�� ������ ���� linkedList��带 ����� ���� linkedList�� �����մϴ�.
	linkedList *new = (linkedList *)malloc(sizeof(linkedList));
	new->data = in;
	new->next = NULL;

	// ù ��尡 �ƴ� ��� ������ ���� ã�ƾ� �ϱ⿡ ������ ���� �����ϰ�, ��� next�� ������ ���� ã���� ���������� �ּҸ� �����մϴ�.
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

// linkedList�� �����͸� ����ϱ� ���� �Լ��Դϴ�.
void printList(linkedList *list)
{
	while (list != NULL)
	{
		printf("%d\n", list->data);
		list = list->next;
	}
}

// linkedList���� n��° ��带 Ž���ϴ� �޼ҵ��Դϴ�.
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

// // n�� 0��° ��ġ���� ���° ��ġ�� ��带 ���� �������� �ǹ��մϴ�.
// void delList(linkedList **list, int n)
// {
// 	linkedList **temp = list;
// 	if (temp == NULL)
// 	{
// 		printf("������ ����Ʈ�� �����ϴ�.");
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

// n�� 0��° ��ġ���� ���° ��ġ�� ��带 ���� �������� �ǹ��մϴ�.
void delList(linkedList **list, int n)
{
	linkedList *temp = *list;
	if (temp == NULL)
	{
		printf("������ ����Ʈ�� �����ϴ�.");
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
	// linkedList�� �������� �˷��ִ� �������Դϴ�.
	linkedList *startNode = NULL;

	// random�� ���� rep���� �����͸� �������� ������ �����Դϴ�. �̸� ���� O(n)�� ����� �� �ֽ��ϴ�.
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