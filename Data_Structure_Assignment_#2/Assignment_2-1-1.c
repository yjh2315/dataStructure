#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* Left, * Right;
}Node;

Node* Insert(Node* node, int data)
{
    if (node == NULL)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
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


int Search(Node* node, int data)
{
    if (node == NULL) {
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
        else
        {
            return node;
        }
    }
}

Node* Delete(Node* node, int data)
{
    if (node == NULL) return NULL;

    if (node->data == data)
    {
        Node* deleteNode = node;
        /*
        TODO: Implement the Delete function conditions
        */
       if(node->Left==NULL&&node->Right==NULL){ //노드 좌우 자식이 NULL일 경우
            //좌우 자식이 없을 경우 연결만 끊으면 되기에 Node를 Free하면 NULL을 가리키게 되기에 더 할 행동이 없습니다.
       }
       else if((node->Left==NULL)==!(node->Right==NULL)){ //노드 좌우 자식 중 하나가 NULL일 경우
            if(node->Left==NULL){
                
            }else{

            }
       }else{                                        //노드 좌우 자식 둘 다 NULL

       }

        free(deleteNode);
        return node;
    }
    else
    {
        /*
        TODO: Implement the delete function traversal
        */
        if (node->data > data)
        {
            Delete(node->Left, data);
        }
        else if (node->data < data)
        {
            Delete(node->Right, data);
        }
       
        return node;
    }
}


// BST Print function 

/* Do not Modify on Submition */


int getHeight(Node* node) {
    if (node == NULL) return 0;
    int leftHeight = getHeight(node->Left);
    int rightHeight = getHeight(node->Right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printLevel(Node* node, int level, int currentLevel, int indentSpace) {
    if (node == NULL) {
        if (currentLevel == level) {
            for (int i = 0; i < indentSpace; i++) printf(" ");
        }
        return;
    }
    if (level == currentLevel) {
        printf("%*s%d", indentSpace, "", node->data);
    }
    else {
        printLevel(node->Left, level, currentLevel + 1, indentSpace);
        printLevel(node->Right, level, currentLevel + 1, indentSpace);
    }
}

void ShowInOrder(Node* root) {
    int height = getHeight(root);
    int indentSpace = 2;
    for (int i = 0; i < height; i++) {
        printLevel(root, i, 0, indentSpace * (height - i));
        printf("\n");
    }
    printf("\n");
}

// Main Function

/* Do not Modify on Submition */

int main()
{
    Node* root = NULL;

    //INSERT
    root = Insert(root, 20);
    root = Insert(root, 10);
    root = Insert(root, 32);
    root = Insert(root, 4);
    root = Insert(root, 13);
    root = Insert(root, 25);
    root = Insert(root, 55);

    //SHOW
    ShowInOrder(root);
    /*
       20
    10    32
  4  13  25  55
    */

    //SEARCH
    printf("Node: %d\n", Search(root, 12));
    /*
    No Node 12 Node: 0
    */
    //SEARCH
    printf("Node %d\n", Search(root, 13));
    /*
    Node: 13
    */

    //DELETE
    root = Delete(root, 32);

    ShowInOrder(root);
    /*
       20
    10    55
  4  13  25
    */
}
