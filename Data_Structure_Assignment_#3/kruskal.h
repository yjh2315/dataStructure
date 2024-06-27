#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int depart, dest;
    int weight;
} Edge;

//출발, 도착지와 가중치를 구조로 갖는 edge 구조체를 선언합니다.

typedef struct {
    int parent;
    int rank;
} Subset;
// 

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    //subsets[i]의 parent가 i가 아니라면, 다른 subset과 union되어 계층화된것이기에 재귀로 호출하여 해당 subset의 root parent를 찾습니다.
    return subsets[i].parent;
}

void Union(Subset subsets[], int a, int b) {
    char rootA = find(subsets, a);
    char rootB = find(subsets, b);

    if (subsets[rootA].rank < subsets[rootB].rank)
        subsets[rootA].parent = rootB;
    else if (subsets[rootA].rank > subsets[rootB].rank)
        subsets[rootB].parent = rootA;
    else {
        subsets[rootB].parent = rootA;
        subsets[rootA].rank++;
    }
}

int compare(const void *a, const void *b) {
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight - b1->weight;
    // a의 weight, b의 weight 를 비교해서 위 식을 계산한 값이 양수라면 값을 변경합니다.(qsort 비교시 활용)
}

void kruskal(Edge graph[], int V , int E){
    // V : 정점의 개수, E : edge의 개수

    qsort(graph, E, sizeof(Edge), compare);
    Subset *set = (subset*)malloc(V * sizeof(Subset));
    for(int i=0; i<V, i++){
        set[i].parent = i;
        set[i].rank = 0;
    }
    
}

int main(void){


}