#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <string>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> P;

#define MAX_N 300
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
int W=0;
int H=0;

int main(){
    while(scanf("%d", &n)){
        W = 0, H = 0;
        for(int inp = 0; inp < n; inp++){
            scanf("%d %d %d", &meteor_x, &meteor_y, &meteor_t);
            
            if(meteor_t == 0){
                meteor_t = -1;
            }
            for(int i = 0; i < 5 ; i++){
                int nx = meteor_x + dx[i], ny = meteor_y + dy[i];
                // if( nx >= 0 && ny >= 0 && ( meteor_map[nx][ny] == 0 || meteor_map[nx][ny] >= meteor_t)){
                if( nx >= 0 && ny >= 0 && meteor_map[nx][ny] == 0) meteor_map[nx][ny] = meteor_t;
                // }
            }
            
            W = max(W, meteor_x);
            H = max(H, meteor_y);
        }
        W += 2;
        H += 2;

        // printf("calc %d, %d\n", W , H);

        // initialize
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H ; j++){
                d[i][j] = INF;
                if(meteor_map[i][j] == -1){
                    meteor_map[i][j] = 0;
                }else if(meteor_map[i][j] == 0){
                    meteor_map[i][j] = METEOR_INF;
                }
                // printf("%d,", meteor_map[i][j]);
            }
            // printf("\n");
        }

        // queue push
        queue<P> que;
        // initialize push
        que.push(P(0, 0));
        d[0][0] = 0;

        int res = -1;

        // bfs loop
        while(que.size()){
            P p = que.front(); que.pop();
            if(res == -1 ) res = d[p.first][p.second];
            // printf("loop %d,%d,%d\n", p.first, p.second, d[p.first][p.second]);
            for(int i = 0; i < 4 ; i++){
                int nx = p.first + dx[i], ny = p.second + dy[i];
                if(0 <= nx && nx < W && 0 <= ny && ny < H && d[p.first][p.second]+1 < meteor_map[nx][ny] && d[nx][ny] == INF){
                    que.push(P(nx,ny));
                    d[nx][ny] = d[p.first][p.second] + 1;
                }
            }
            if(meteor_map[p.first][p.second] != METEOR_INF){
                if(res == d[p.first][p.second]) res = -1;
                d[p.first][p.second] = -1;
            }
        }
        /*
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H ; j++){
                // printf("%d,", d[i][j]);
                if(d[i][j] != -1 && d[i][j] != INF){
                    if(res == -1){
                        res = d[i][j];
                    }else{
                        res = min(res, d[i][j]);
                    }
                }
            }
            // printf("\n");
        }*/
        // result
        printf("%d",res);
    }
    return 0;
}

