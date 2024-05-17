
#include <stdio.h>      //printf,  fprintf
#include <stdlib.h>     //malloc,  exit
#include <string.h>     //memset    ??
#include <stdbool.h>    //bool,  true,  false


#define IS_EMPTY(ptr) (!(ptr))
#define IS_FULL(ptr) (!(ptr))


//圖的點上限
#define MAX_VERTEX 50


typedef struct node* node_ptr;
typedef struct node{
    int vertex;
    node_ptr link;
}node;

node_ptr graph[MAX_VERTEX];     //用來表示  array的指標。0,1,2....n-1

int n = 0;          //  表 節點(指標)個數









//*********************************************************************************************************************

//MARK: release memory


void release_graph(void)
{
    for(int i = 0; i < n; i++){
        node_ptr delete_node;
        while(graph[i]){
            delete_node = graph[i];
            graph[i] = delete_node -> link;
            
            free(delete_node);
        }
        graph[i] = NULL;
    }
    n = 0;              //全域得值。原本是8改為0
}







//*********************************************************************************************************************



//MARK: - 圖的走訪

bool visited[MAX_VERTEX];    //用來標記沒有走訪過的點,    與 graph[] 是不同的但裡面順序剛好相通


//走訪前 清空標記

void reset_visited (void)
{
    for(int i = 0 ; i < n ; i++){
        visited[i] = false;
    }
}



//MARK: 深度尋訪 (DFS)

void dfs(int v)
{
    visited[v] = true;
    printf(" %d", v);
    
    // 走訪與 v 相鄰且無走過的點
    
    node_ptr w;
    
    for(w = graph[v]; w; w = w -> link){
        if(!visited[w -> vertex]){
            dfs(w -> vertex);
        }
    }
}
//*********************************************************************************************************************


//MARK: 廣度尋訪 搭配(queue)


typedef struct queue* queue_ptr;
typedef struct queue{
    int vertexq;
    queue_ptr link;
}queue;



int deleteq(queue_ptr *front)
{
    
    if(IS_EMPTY(*front)){
        fprintf(stderr, "The memory is empty\n");
        exit(1);
    }
    
    int vertexq;
    queue_ptr delete_node;
    
    delete_node = *front;
    vertexq = delete_node -> vertexq;
    (*front) = delete_node -> link;
    
    free(delete_node);
    
    return vertexq;
    
}







void addq(queue_ptr *front,queue_ptr *rear,int vertexq)
{
    
    queue_ptr new_node = (queue_ptr)malloc(sizeof(queue));
    
    if(IS_FULL(new_node)){
        fprintf(stderr,"The memory is full\n");
        exit(1);
    }
    
    
    new_node -> vertexq = vertexq;
    new_node -> link = NULL;
    
    
    if(*front){
        (*rear) -> link = new_node;
    }
    
    else{
        (*front) = new_node;
    }
    
    *rear = new_node;
}




void bfs(int v)
{
    //佇列 初始化
    queue_ptr front = NULL, rear = NULL;
    
    
    //加入第一次走訪的點 加進佇列
    addq(&front,&rear,v);
    visited[v] = true;
    printf(" %d",v);
    
  
    
    
    // 依序將點從佇列中刪除， 並走訪該點(相鄰)且(未走過的點) 並加進佇列中
    while (front) {
        v = deleteq(&front);
        
        for(node_ptr w = graph[v]; w; w = w -> link){
            if(!visited[w->vertex]){
                addq(&front, &rear, w->vertex);
                visited[w->vertex] = true;
                printf(" %d", w->vertex);
            }
        }
    }
}




//*********************************************************************************************************************


// 建立車廂

node_ptr create_node(int vertex, node_ptr link)
{
    node_ptr new_node = (node_ptr)malloc(sizeof(node));
    
    new_node -> link = link;
    new_node -> vertex = vertex;
    
    return new_node;
}






//MARK: create_sample_graph

void create_sample_graph(void)
{
    node_ptr tmp;               //拿來共用的指標
    
    
    // 0 -> 1 -> 2
    tmp = create_node(2, NULL);
    tmp = create_node(1, tmp);
    graph[0] = tmp;             //用來表示（指標）＝ （指標）
    
    
    // 1 -> 0 -> 3 -> 4
    tmp = create_node(4, NULL);
    tmp = create_node(3, tmp);
    tmp = create_node(0, tmp);
    graph[1] = tmp;
    
    
    // 2 -> 0 -> 5 -> 6
    tmp = create_node(6, NULL);
    tmp = create_node(5, tmp);
    tmp = create_node(0, tmp);
    graph[2] = tmp;
    
    
    // 3 -> 1 -> 7
    tmp = create_node(7, NULL);
    tmp = create_node(1, tmp);
    graph[3] = tmp;

    // 4 -> 1 -> 7
    tmp = create_node(7, NULL);
    tmp = create_node(1, tmp);
    graph[4] = tmp;

    // 5 -> 2 -> 7
    tmp = create_node(7, NULL);
    tmp = create_node(2, tmp);
    graph[5] = tmp;

    // 6 -> 2 -> 7
    tmp = create_node(7, NULL);
    tmp = create_node(2, tmp);
    graph[6] = tmp;

    // 7 -> 3 -> 4 -> 5 -> 6
    tmp = create_node(6, NULL);
    tmp = create_node(5, tmp);
    tmp = create_node(4, tmp);
    tmp = create_node(3, tmp);
    graph[7] = tmp;
    
    
    n = 8;
    
}



//*********************************************************************************************************************


/*MARK: 範例圖

*  0 -> 1 -> 2
*  1 -> 0 -> 3 -> 4
*  2 -> 0 -> 5 -> 6
*  3 -> 1 -> 7
*  4 -> 1 -> 7
*  5 -> 2 -> 7
*  6 -> 2 -> 7
*  7 -> 3 -> 4 -> 5 -> 6

*/
void create_sample_graph(void);


int main()
{
    //建立圖型
    create_sample_graph();
    
    
    //印出相鄰串列
    
    printf("Graph:\n");
    
    node_ptr nptr = NULL;      //用來輔助的 指標
    
    for(int i =0 ; i<n ; i++){
        printf("%d", i);
        for( nptr = graph[i] ; nptr ; nptr = nptr -> link){
            printf(" -> %d", nptr -> vertex);
        }
        printf("\n");
    }
    
    printf("\n");
    
    
    
    //深度尋訪

    printf("DFS:");
    reset_visited();
    dfs(0);
    printf("\n");
    
    
    
    //廣度尋訪
    
    printf("BFS:");
    reset_visited();
    bfs(0);
    printf("\n");
    
    
    //釋放記憶體
    release_graph();
    
    
    return 0;
    
}




//*********************************************************************************************************************




