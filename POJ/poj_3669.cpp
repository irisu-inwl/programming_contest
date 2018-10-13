#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <string>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> P;

// 0*0は壁のため+2、メテオが一番端(300)に来たらそこから逃れるために302マスに移動する必要があるので+2,よって304マスとる。
#define MAX_N 304
#define MAX_T 1000
#define MAX_M 50000
#define INF 1024
#define METEOR_INF 64000

// メテオ衝突時間になったらフィールドを破壊する INFにする
int d[MAX_N][MAX_N];

int dx[5] = {1, 0, -1, 0, 0};
int dy[5] = {0, 1, 0, -1, 0};
int meteor_x;
int meteor_y;
int meteor_t;
int meteor_map[MAX_N][MAX_N];
int n; // <= 50000
int W=1;
int H=1;

int main(){
    // while(scanf("%d", &n)){
    scanf("%d", &n);
    W = 1, H = 1;

    // map initialize
    for(int i = 0; i < MAX_N; i++){
        for(int j = 0; j < MAX_N ; j++){
            d[i][j] = INF;
            if(i != 0 && j != 0) meteor_map[i][j] = METEOR_INF;
        }
    }

    for(int inp = 0; inp < n; inp++){
        scanf("%d %d %d", &meteor_x, &meteor_y, &meteor_t);
        meteor_x++; meteor_y++;

        for(int i = 0; i < 5 ; i++){
            int nx = meteor_x + dx[i], ny = meteor_y + dy[i];
            if( meteor_map[nx][ny] > meteor_t ){
                meteor_map[nx][ny] = meteor_t;
            }
        }
    }

    // queue push
    int start_x = 1, start_y = 1;
    queue<P> que;
    // initialize push
    que.push(P(start_x, start_y));
    d[start_x][start_y] = 0;

    // bfs loop
    while(que.size()){
        P p = que.front(); que.pop();
        if(meteor_map[p.first][p.second] == METEOR_INF){
            printf("%d\n", d[p.first][p.second]);
            return 0;
        }
        for(int i = 0; i < 4 ; i++){
            int nx = p.first + dx[i], ny = p.second + dy[i];
            if(d[p.first][p.second]+1 < meteor_map[nx][ny] && d[p.first][p.second]+1 < d[nx][ny]){
                que.push(P(nx,ny));
                d[nx][ny] = d[p.first][p.second] + 1;
            }
        }
        if(meteor_map[p.first][p.second] != METEOR_INF){
            d[p.first][p.second] = -1;
        }
    }
    // result
    printf("%d", -1);
    return 0;
}
