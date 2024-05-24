#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void moveElement(int **dynamic, int from, int destination, int *size)
{
    if (destination == 1)
    {
        // destination 방향으로 *size-from 횟수만큼 dynamicArray를 size부터 from까지 오른쪽으로 이동
        //  to가 1이라면 값을 from부터 오른쪽으로 이동(맨 뒷 값부터 이동)
        int repeat = *size - from;
        for (int i = 0; i < repeat; i++)
        {
            int i1 = *size - i;
            int i2 = *size - i - 1;
            (*dynamic)[i1] = (*dynamic)[i2];
        }
    }
    else
    {
        // destination 방향으로 *size-from 횟수만큼 dynamicArray를 from부터 size까지 왼쪽으로 이동
        //  to가 나머지 값이라면 값을 from 뒤부터 왼쪽으로 이동(index가 0에서 가까운 순서대로 이동)
        int repeat = *size - from;
        for (int i = 0; i < repeat; i++)
        {
            int i1 = from + i;
            int i2 = from + i + 1;
            (*dynamic)[i1] = (*dynamic)[i2];
        }
    }
}

// 입력되는 자리(to)가 이미 값이 차있는 자리라면 to부터 nowMax까지 값들을 오른쪽으로 이동 후 to에다 값 대입.
void addElement(int **dynamic, int *nowMax, int to, int value)
{
    if (*nowMax >= to && *nowMax != 0)
    {
        moveElement(dynamic, to, 1, nowMax);
        (*dynamic)[to] = value;
    }
    else
    {
        (*dynamic)[*nowMax] = value;
    }
    (*nowMax)++;
}

// 입력되는 자리(to)가 값들이 차있는 자리라면 to 이후부터 nowMax까지 값들을 왼쪽으로 이동한다.(삭제)
void delElement(int **dynamic, int *nowMax, int to, int size)
{
    if (*nowMax == size)
    {
        if (to == size - 1)
        {
            (*dynamic)[*nowMax] = 0;
            (*nowMax)--;
        }
    }
    if (*nowMax >= to && *nowMax != 0)
    {
        moveElement(dynamic, to, 0, nowMax);
        (*dynamic)[*nowMax] = 0;
        (*nowMax)--;
    }
}

int main()
{
    int size = 10;
    int nowMax = 0;
    int *dynamicArray = (int *)malloc(sizeof(int) * size);

    //------------------------------------------------//

    // //          1. 구현부
    // // 앞에서 추가, 중간에서 추가, 끝에서 추가
    // addElement(&dynamicArray, &nowMax, 0, 10);
    // for (int i = 0; i < 7; i++)
    // {
    //     addElement(&dynamicArray, &nowMax, 0, 1);
    // }
    // addElement(&dynamicArray, &nowMax, 4, 11);
    // addElement(&dynamicArray, &nowMax, nowMax, 12);
    // for (int i = 0; i < size; i++)
    // {
    //     printf("%d\n", dynamicArray[i]);
    // }

    // // 끝에서 삭제, 끝에서 삭제, 중간에서 삭제, 앞에서 삭제
    // delElement(&dynamicArray, &nowMax, size - 1, size);
    // delElement(&dynamicArray, &nowMax, nowMax, size);
    // delElement(&dynamicArray, &nowMax, 4, size);
    // delElement(&dynamicArray, &nowMax, 0, size);

    // for (int i = 0; i < size; i++)
    // {
    //     printf("%d\n", dynamicArray[i]);
    // }

    // // 탐색부
    // printf("%d\n", dynamicArray[3]);
    //------------------------------------------------//

    //              2. 시간 복잡도 분석, 공간 복잡도 분석

    clock_t start, end;
    double res;
    // start와 end를 통해 프로그램 실행에 걸린 시간을 계산합니다.
    // start = clock();
    for (int i = 0; i < size; i++)
    {
        // int a = dynamicArray[0];
        addElement(&dynamicArray, &nowMax, nowMax, 1);
        //
    }

    start = clock();
    for (int i = 0; i < size; i++)
    {
        delElement(&dynamicArray, &nowMax, 0, size);
    }

    end = clock();
    res = (double)(end - start) / CLOCKS_PER_SEC;
    printf("DA %d size: 삭제시간 : %f", size, res);
}