#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20
//typedef char VertexType;

#define FALSE 0
#define TRUE 1
short int visitq[MAX_VERTEX];

typedef struct Queue {
    int Queue[MAX_VERTEX];
    int front;
    int rear;
}Queue;
typedef struct Vertex {
    int num; /* vertex number */
    struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;


typedef struct VertexHead {
    //VertexType data;
    Vertex* head;
    int visit;
}VertexHead;

typedef struct Graph {
    VertexHead* vlist;
    int numEdge;
}Graph;

int CreateGraph(Graph* G); /* empty graph creation */
void destroyGraph(Graph* G); /* deallocating all allocated memory */
int insertVertex(Graph* G); /* vertex insertion */
void deVertex(Graph* G, int v); /* vertex deletion */
//void deVertex(Graph* G);
void insertEdge(Graph* G); /* new edge creation between two vertices */
void  deleteEdge(Graph* head); /* edge removal */
/* depth firt search using stack */
void depthFS(Graph head, int v);

void breadthFS(Graph head,int v); /* breadth first search using queue */

int QueueEmpty(Queue Q);
void EnQueue(Queue* Q, int e);
void DeQueue(Queue* Q, int* e);

void printGraph(Graph* head); /* printing graph with vertices and edges */

int  CreateGraph(Graph* G) {
    //    if(G->vlist!=NULL){
    //        destroyGraph(G);
    //        return 0;
    //    }

    G->vlist = (VertexHead*)malloc(sizeof(VertexHead[MAX_VERTEX]));//vlist 할당

    for (int i = 0; i < MAX_VERTEX; i++) {
        G->vlist[i].visit = 0;
    }
    if (G->vlist == NULL) {
        printf("fail");
        return 0;
    }
    return 0;

}
void destroyGraph(Graph* G) {
    for (int i = 0; i < MAX_VERTEX; i++) {
        deVertex(G, i);
    }

}
void deVertex(Graph* G, int v) {
    Vertex* p = G->vlist[v].head;
    G->vlist[v].visit = 0;
    Vertex* pre = NULL;
    while (p != NULL) {
        pre = p;
        p = p->link;
        free(pre);
    }
    free(G->vlist[v].head);
}


int insertVertex(Graph* G) {
    int i = 0;
    if (G->vlist == NULL) {
        printf("fail");
        return 0;
    }
    printf("vertex:\n");

    scanf("%d", &i);
    G->vlist[i].head = NULL;           //edge pointer 초기화
    G->vlist[i].visit = 1;
    return 0;
}

void insertEdge(Graph* G) {
    int i, j, k;
    printf("edge 수:\n");
    scanf("%d", &G->numEdge);
    printf("edge[v1][v2]\n");

    for (k = 0; k < G->numEdge; k++) {
        scanf("%d%d", &i, &j);
        Vertex* p = (Vertex*)malloc(sizeof(Vertex));//삽입하고 싶은 vertex 할당
        p->num = j;                                //vertex number 저장
        p->link = G->vlist[i].head;            //head insert
        G->vlist[i].head = p;

    }

}

void depthFS(Graph head, int v) {
    Vertex* w = head.vlist[v].head;
    visitq[v] = TRUE;
    printf("%5d", v);
    for (; w; w = w->link)
        if (!visitq[w->num])
            depthFS(head, w->num);

}

void deleteEdge(Graph* G) {
    int i, j;

    printf("삭제 edge[v1][v2]:\n");

    scanf("%d%d", &i, &j);
    Vertex* p = G->vlist[i].head;

    Vertex* pre = p;
    while (p->num != j || p->link == NULL) {
        pre = p;
        p = p->link;
    }
    if (p->num == j) {
        pre->link = p->link;
        free(p);
        p = NULL;
    }
    else printf("찾을 수 없음");//p->link == NULL

}

void printGraph(Graph* G) {

    printf("vertex:\n");
    for (int a = 0; a < MAX_VERTEX; a++) {
        if (G->vlist[a].visit == 1) {//초기화 됨
            printf("%d  ", a);
        }
    }
    printf("Graph:\n");
    for (int i = 0; i < MAX_VERTEX; i++) {
        if (G->vlist[i].visit == 1) {
            Vertex* p = G->vlist[i].head;
            while (p) {

                printf("edge[%d][%d]", i, p->num);
                p = p->link;
            }
        }
    }
    printf("\n");


}
void breadthFS(Graph head, int v) {
    //int i;
   // Vertex* p;
//    Queue Q;
//    Q.front=0;
//    Q.rear=0;
//    printf("5%d", v);
//    visitq[v] = TRUE;
//    EnQueue(&Q, v);
//    while (Q.front) {
//        DeQueue(&Q, &v);


}
int QueueEmpty(Queue Q) {
    return Q.front == Q.rear;
}
void EnQueue(Queue* Q, int e) {
    if ((Q->rear + 1) % MAX_VERTEX == Q->front)
        return;
    Q->Queue[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX_VERTEX;
}
void DeQueue(Queue* Q, int* e) {
    if (Q->rear == Q->front)
        return;
    *e = Q->Queue[Q->front];
    Q->front = (Q->front + 1) % MAX_VERTEX;
}
int main() {

    Graph head;
    char command;

    int v;

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                           graph                                \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize              = z      print                     = p \n");
        printf(" vertex insertion        = i      vertex deletion           = d \n");
        printf(" Edge insertion          = r      depth firt search         = t \n");
        printf(" breadth first search    = b      Edge deletion             = l \n");
        printf(" Quit                    = q                                    \n");

        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            CreateGraph(&head);
            break;
        case 'q': case 'Q':
            destroyGraph(&head);
            break;
        case 'i': case 'I':

            /*printf("Inser vertex = ");
            scanf("%d", &v);*/
            insertVertex(&head);
            break;
        case 'd': case 'D':

            printf("Detele vertex = ");
            scanf("%d", &v);
            deVertex(&head, v);
            break;

        case 'r': case 'R':
            /*printf("v1 vertex = ");
            scanf("%d", &v1);
            printf("v2 vertex = ");
            scanf("%d", &v2);*/
            insertEdge(&head);

            break;
        case 't': case 'T':

            printf("시작한 vertex num");
            scanf("%d", &v);
            depthFS(head, v);
            break;
        case 'b': case 'B':
            printf("시작한 vertex num");
            scanf("%d", &v);
            breadthFS(head,v);
            break;
        case 'l': case 'L':

            deleteEdge(&head);
            break;

        case 'p': case 'P':
            printGraph(&head);
            break;

        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}




