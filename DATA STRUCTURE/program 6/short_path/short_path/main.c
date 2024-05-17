
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>     //??


#define MAX_VERTICES 6


/* 無限距離，表示不存在的邊，  "其值可自行調整"  ，但須符合以下條件：
 *
 *  1. 此數值必須大於成本矩陣中的任何數值，
 *  2. 此數值必須不會造成 `distance[u] + cost[u][w]` 溢位。
 */

#define INF_DST 1000





// 找最短距離且未檢查過的

int choose()
{
    
}










/* 計算從 `v` 點到其他點的最短距離。
 *
 * cost       : 圖的相鄰矩陣
 *
 * distance[i]: 從 `v` 點到 `i` 點的最短距離。
 *
 * found[i]   : 為 `0` 表示從 `v` 點到 `i` 點的路徑還沒找到，`1` 則為找到了。
*/


void shortestpath(int v, int cost[][MAX_VERTICES], int distance[], int n, bool found[])
{
    
    for(int i = 0; i < n; i++){
        found[i] = false;
        distance[i] = cost[v][i];
    }
    
    found[v] = true;
    distance[v] = 0;
    for(int i = 0; i < n-1; i++){
        
        int u = choose(distance , n found);
    }
        
    
}









int main ()
{
    //成本矩陣 (有向圖)
    int cost[][MAX_VERTICES] = {
        {       0,      50,      10, INF_DST,      45, INF_DST },
        { INF_DST,       0,      15, INF_DST,      10, INF_DST },
        {      20, INF_DST,       0,      15, INF_DST, INF_DST },
        { INF_DST,      20, INF_DST,       0,      35, INF_DST },
        { INF_DST, INF_DST,      30, INF_DST,       0, INF_DST },
        { INF_DST, INF_DST, INF_DST,       3, INF_DST,       0 }
    };
    
    
    //用來  “存從起點出發”  最短的距離
    int distance[MAX_VERTICES] = {0};
    
    //用來  標記起點出發時，是否有最短路徑
    bool found[MAX_VERTICES] = {0};
    
    //圓的點數              ？？
    int n = MAX_VERTICES;
    
    //起始點
    int start;
    
    
    
    //印出成本矩陣
    printf("Cost Matrix:\n");
    
    for(int i = 0; i < n; i++){
        
        for(int j = 0; j < n; j++){
            
            if(cost[i][j] == INF_DST){
                printf(" inf");
            }
        }
        printf("\n");
    }
    printf("\n");
    
    
    for (start = 0; start < MAX_VERTICES; start++){
        
        //計算  "start" 到其他點的距離。
        shortestpath(start, cost, distance, n, found);
        //印出結果
    }
    
    
}

