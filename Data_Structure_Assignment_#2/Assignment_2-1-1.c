#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *Left, *Right;
} Node;

Node *Insert(Node *node, int data)
{
    if (node == NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->Left = NULL;
        newNode->Right = NULL;

        return newNode;
    }
    else
    {
        /*
        TODO: Fill the conditions in Insert function
        */
        if (node->data > data)
        {
            node->Left = Insert(node->Left, data);
            return node;
        }
        /*
        TODO: Fill the conditions in Insert function
        */
        else if (node->data < data)
        {
            node->Right = Insert(node->Right, data);
            return node;
        }
        else
        {
            return node;
        }
    }
}

int Search(Node *node, int data)
{
    if (node == NULL)
    {
        printf("No Node %d ", data);
        return NULL;
    }

    if (node->data == data)
    {
        return node->data;
    }
    else
    {
        /*
        TODO: Implement the Search function conditions
        */
        if (node->data > data)
        {
            Search(node->Left, data);
        }
        else if (node->data < data)
        {
            Search(node->Right, data);
        }
    }
}

Node *Delete(Node *node, int data)
{
    if (node == NULL)
        return NULL;

    if (node->data == data)
    {
        Node *deleteNode = node;
        /*
        TODO: Implement the Delete function conditions
        */
        if (node->Left == NULL)
        {
            // 노드의 왼쪽 주소가 가리키는 부분이 NULL일 경우 -- 자식이 없는 경우(리프노드) or 왼쪽 노드만 없을 경우이다. 단순하게 오른쪽 노드를 전달하고, 노드를 삭제한다.
            Node *tempNode = node->Right;
            free(deleteNode);
            return tempNode;
        }
        else if (node->Right == NULL)
        {
            // 노드의 오른쪽이 가리키는 부분이 NULL인 경우 - 오른쪽이 가리키는 노드만 없을 경우이다.
            Node *tempNode = node->Left;
            free(deleteNode);
            return tempNode;
        }
        // 자식노드가 모두 있을 경우이다.
        Node *tempNode = node;
        tempNode = tempNode->Right;
        while (tempNode->Left != NULL)
        {
            tempNode = tempNode->Left;
        }
        node->data = tempNode->data;

        node->Right = Delete(node->Right, tempNode->data);
        return node;
    }
    else
    {
        /*
        TODO: Implement the delete function traversal
        */
        if (node->data > data)
        {
            node->Left = Delete(node->Left, data);
            /*노드를 탐색한다. 다만 현재 데이터보다 값이 더 작으니 왼쪽을 탐색하고, 왼쪽의 주소는 Delete 결과 node로 설정한다.
            재귀적으로 삭제 이후 주소를 돌려주기 위한 방식이다. 탐색 결과 그 값이 타겟이 아닐 경우 return node를 통해 왼쪽 노드를 다시 원위치해준다.
            */
        }
        else if (node->data < data)
        {
            node->Right = Delete(node->Right, data);
            // 왼쪽 탐색과 유사하다.
        }

        return node;
    }
}

// BST Print function

/* Do not Modify on Submition */

int getHeight(Node *node)
{
    if (node == NULL)
        return 0;
    int leftHeight = getHeight(node->Left);
    int rightHeight = getHeight(node->Right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printLevel(Node *node, int level, int currentLevel, int indentSpace)
{
    if (node == NULL)
    {
        if (currentLevel == level)
        {
            for (int i = 0; i < indentSpace; i++)
                printf(" ");
        }
        return;
    }
    if (level == currentLevel)
    {
        printf("%*s%d", indentSpace, "", node->data);
    }
    else
    {
        printLevel(node->Left, level, currentLevel + 1, indentSpace);
        printLevel(node->Right, level, currentLevel + 1, indentSpace);
    }
}

void ShowInOrder(Node *root)
{
    int height = getHeight(root);
    int indentSpace = 2;
    for (int i = 0; i < height; i++)
    {
        printLevel(root, i, 0, indentSpace * (height - i));
        printf("\n");
    }
    printf("\n");
}

// Main Function

/* Do not Modify on Submition */

int main()
{
    Node *root = NULL;

    // INSERT
    root = Insert(root, 20);
    root = Insert(root, 10);
    root = Insert(root, 32);
    root = Insert(root, 4);
    root = Insert(root, 13);
    root = Insert(root, 25);
    root = Insert(root, 55);

    // SHOW
    ShowInOrder(root);
    /*
       20
    10    32
  4  13  25  55
    */

    // SEARCH
    printf("Node: %d\n", Search(root, 12));
    /*
    No Node 12 Node: 0
    */
    // SEARCH
    printf("Node %d\n", Search(root, 13));
    /*
    Node: 13
    */

    // DELETE
    root = Delete(root, 32);

    ShowInOrder(root);
    /*
       20
    10    55
  4  13  25
    */
}
