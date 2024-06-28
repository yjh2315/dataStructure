#include <stdio.h>
#define BIG 1000000

typedef struct {
    int arr[20];
    int front;
    int rear;
}Queue;

int printQueue(Queue *que){
    for(int i=0; i<18; i++){
        printf("%d ",que->arr[i]);
    }
    printf(" front: %d, rear: %d \n ", que->front, que->rear);
}

int voidQueue(Queue *que){
    if(que->rear == que->front){
        return 1;
    }
    return 0;
    printQueue(que);
}
void enque(Queue *que,int in){
    que->arr[que->rear++] = in;
    printQueue(que);
}

int deque(Queue *que){
    if(voidQueue(que)==0){
        printQueue(que);
        return que->arr[que->front++];
    }
    //rear이 0이 아니라면 값이 있기에.
}



int graph[18][18];
int res[18];
int visit[18] = {0,};
int lastVisit[18] = {0,};
Queue* queue;

void findNextNode(int node){
    for(int i=1; i<18; i++){
        if(graph[node][i]<BIG&&visit[i]==0){
            int cnt = 0;
            for(int j=1; j<18; j++){
                if(queue->arr[j]==i) cnt++;
            }
            if(cnt==0) enque(queue,i);
            // BIG보다 값이 작고 node에서부터 vertex가 있는 것이고, 방문하지 않았다면 이를 queue에 넣습니다.
        }
    }
}

void findSmall(int node){
    for(int i=1; i<18; i++){
        int temp = graph[node][i];
        if(graph[node][i]<BIG&&i!=node){
            if(res[node]+temp < res[i]){
                //기존 node까지 거리 + node-i까지의 노드 거리 < 기존 i까지의 거리 일 경우 최적경로이기에
                res[i] = res[node]+temp;
                lastVisit[i] = node;
                //값을 갱신하고, 최근 탐색 노드를 node로 변경합니다.
                for(int j=0; j<18; j++){
                    if(lastVisit[j]==i){
                        //최근탐색 노드가 i일 경우(최단거리가 t~i, i-j[바로 vertex로 연결]) t-j도 갱신이 필요하기에, 갱신합니다.
                        res[j] = res[i] + graph[i][j];
                        lastVisit[j] = i;
                    }
                }
                printStatus();
            }
        }
    }
}

void printVisit(){
    printf("visit\n");
    for(int i=1; i<18; i++){
        printf("%d ",visit[i]);
    }
    printf("\n");
}

void printStatus(){
    printf("res : \n");
    for(int i=1; i<17; i++){
        printf("[%d]:%d ", i, res[i]);
    }
    printf("\nlastVisit : \n");
    for(int i=1; i<17; i++){
        printf("[%d]:%d ",i,  lastVisit[i]);
    }
    printf("\n\n");
}

void dijkstra(int start){
    enque(queue, start);
    res[start] = 0;
    visit[start] = 1;
    while(voidQueue(queue)==0){
        if(voidQueue(queue)==0){
            // queue가 비지 않았다면.
            int temp = deque(queue);   
            findNextNode(temp);         // 다음 탐색할 노드를 queue에 넣습니다
            findSmall(temp);            // temp에 해당하는 노드의 값들로 최단거리를 갱신합니다.
            visit[temp] = 1;
            //findSmall로 값을 갱신하고 방문처리
        }
    }
    printStatus();
}


void setGraph(int graph[][18], int from, int to, int weight){
    graph[from][to] = weight;
    graph[to][from] = weight;
}


int main(){
    Queue new = {{0},0,0};
    queue = &new;
    for(int i=0;i<18;i++){
        for(int j=0; j<18; j++){
            graph[i][j] = BIG;
            if(i==j) graph[i][j] = 0;
        }
        res[i] = BIG;
        queue->arr[i] = 0;
    }
    //정점간의 거리를 표현합니다. BIG의 경우 직접 간선이 없는 경우입니다.
    
    setGraph(graph,1,2,3);
    setGraph(graph,1,5,2);
    setGraph(graph,2,3,1);
    setGraph(graph,2,6,5);
    setGraph(graph,3,4,4);
    setGraph(graph,3,7,1);
    setGraph(graph,4,8,6);
    setGraph(graph,5,6,1);
    setGraph(graph,5,9,3);
    setGraph(graph,6,7,5);
    setGraph(graph,6,10,4);
    setGraph(graph,7,8,8);
    setGraph(graph,7,11,2);
    setGraph(graph,8,12,6);
    setGraph(graph,9,10,2);
    setGraph(graph,9,13,2);
    setGraph(graph,10,11,4);
    setGraph(graph,10,14,6);
    setGraph(graph,11,12,6);
    setGraph(graph,11,15,4);
    setGraph(graph,12,16,4);
    setGraph(graph,13,14,3);
    setGraph(graph,14,15,5);
    setGraph(graph,15,16,7);
    //graph 정점을 배열에 삽입합니다.

    dijkstra(1);
}