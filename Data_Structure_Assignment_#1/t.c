#define _CRT_SERCURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct linkedList* pLinkedList;
//LinkedList�� �����͸� pLinkedList�� �����Ͽ� linkedList ����ο� ����߽��ϴ�.

typedef struct linkedList {
    int data;
    pLinkedList next;
}linkedList;
//linkedList�� int���� data�� ������, ���� linkedList�� �ּ�(������)�� ���� ����ü�� �����߽��ϴ�.

void newList(linkedList** list, int in) {
    //doublePointer������ linkedList�� ������ ���� linkedList��带 ����� ���� linkedList�� �����մϴ�.
    linkedList* new = (linkedList*)malloc(sizeof(linkedList));
    new->data = in;
    new->next = NULL;

    //ù ��尡 �ƴ� ��� ������ ���� ã�ƾ� �ϱ⿡ ������ ���� �����ϰ�, ��� next�� ������ ���� ã���� ���������� �ּҸ� �����մϴ�.
    pLinkedList temp = *list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}

void initList(linkedList** list, int in) {
    linkedList* new = (linkedList*)malloc(sizeof(linkedList));
    new->data = in;
    new->next = NULL;

    //ù ��尡 ���ԵǴ� ��츦 ����ó���ϱ� ���ؼ� �Ʒ��� ���� *list�� �Ҵ�� �κ��� ������ ���� ���� ��尡 ù ��尡 �ǵ��� �����մϴ�.
    if ((*list) == NULL) {
        *list = new;
    }
}

//linkedList�� �����͸� ����ϱ� ���� �Լ��Դϴ�.
void printList(linkedList* list) {
    while (list != NULL) {
        printf("%d\n", list->data);
        list = list->next;
    }
}

int main() {
    //linkedList�� �������� �˷��ִ� �������Դϴ�.
    linkedList* startNode = NULL;

    //random�� ���� rep���� �����͸� �������� ������ �����Դϴ�. �̸� ���� O(n)�� ����� �� �ֽ��ϴ�.
    srand(time(NULL));
    int rep = 5;
    initList(&startNode, rand() % 100);
    for (int i = 0; i < rep - 1; i++) {
        newList(&startNode, rand() % 100);
    }
}