#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
    int depart, dest;
    int weight;
} Edge;
//출발, 도착지와 가중치를 구조로 갖는 edge 구조체를 선언합니다.

void Union(int* sets, int a, int b, int len) {
    //a와 b의 set 값이 다르면 (서로 다른 집합이면), 하나의 집합으로 만듭니다.
    if (sets[a] != sets[b]) {
        int temp = sets[b];
        for (int i = 0; i < len; i++) {
            //len만큼 탐색하여 b와 set 값이 같은 데이터를 모두 set[a]로 바꿉니다.(집합 표시)
            if (sets[i] == temp) {
                sets[i] = sets[a];
            }
        }
    }
}

int compare(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
    // a의 weight, b의 weight 를 비교해서 위 식을 계산한 값이 양수라면 값을 변경합니다.(qsort 비교시 활용)
}

void kruskal(Edge graph[], int V, int E) {
    // V : 정점의 개수, E : edge의 개수

    qsort(graph, E, sizeof(Edge), compare);
    //Edge 타입의 graph를 정렬합니다.
    int* set = (int*)malloc((V+1) * sizeof(int));

    for (int i = 0; i <= V; i++) {
        set[i] = i;
    }
    // set 배열을 초기화합니다.(초기화는 자기 자신이 하나의 그룹이 되도록)

    Edge *result = (Edge*)malloc(sizeof(Edge)*V);
    int i = 0;        // kruskal 결과 edge의 개수 ( V-1개가 최대 )
    int c = 0;        // kruskal 검사 반복횟수    ( E번 반복이 최대 )

    while (i < V - 1 && c < E) {
        Edge nextEdge = graph[c];
        int depart = set[nextEdge.depart];
        int dest = set[nextEdge.dest];
        //다음 edge를 받아와 depart와 dest의 값을 저장한 후, cycle이 생기지 않도록 값이 다를 때만 Union을 실행하고, 해당 edge를 result에 저장합니다.

        if (depart != dest) {
            result[i] = nextEdge;
            Union(set, depart, dest, V+1);
            i++;
        }
        // 출발 노드와 도착 노드가 같은 셋이 아니라면 둘을 연결합니다. 그 과정 중 set들을 연결했다는 의미의 Union함수를 실행합니다.

        c++;
    }

    printf("MST:\n");
    for (int j = 0; j < i; ++j)
        printf("route: %3d -%3d   weight: %3d\n", result[j].depart, result[j].dest, result[j].weight);

    free(set);
    free(result);

}

int main(void) {
    Edge graph[] = {
        {1,5,2},
        {2,3,1},
        {2,6,5},
        {3,4,4},
        {3,7,1},
        {4,8,6},
        {5,6,1},
        {5,9,3},
        {6,7,5},
        {6,10,4},
        {7,8,8},
        {7,11,2},
        {8,12,6},
        {9,10,2},
        {9,13,2},
        {10,11,4},
        {10,14,6},
        {11,12,6},
        {11,15,4},
        {12,16,4},
        {13,14,3},
        {14,15,5},
        {15,16,7}
    };

    int V = 16; // 정점의 수
    int E = sizeof(graph) / sizeof(graph[0]); // 간선의 수

    kruskal(graph, V, E);

    return 0;
}