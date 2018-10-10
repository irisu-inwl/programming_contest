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

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int meteor[MAX_M][3];
int meteor_map[MAX_N][MAX_N];
int n; // <= 50000
int W=0;
int H=0;

int main(){
    while(scanf("%d", &n)){
        W = 0, H = 0;
        int spend_time = 0;
        int meteor_index = 0;
        for(int inp = 0; inp < n; inp++){
            scanf("%d %d %d", &meteor[inp][0], &meteor[inp][1], &meteor[inp][2]);
            if(meteor[inp][2] == 0){
                meteor_map[meteor[inp][0]][meteor[inp][1]] = METEOR_INF;
            }else{
                meteor_map[meteor[inp][0]][meteor[inp][1]] = meteor[inp][2];
            }
            
            W = max(W, meteor[inp][0]);
            H = max(H, meteor[inp][1]);
        }
        W += 2;
        H += 2;

        printf("calc %d, %d\n", W , H);

        // initialize
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H ; j++){
                d[i][j] = INF;
                if(meteor_map[i][j] == METEOR_INF){
                    meteor_map[i][j] = 0;
                }else{
                    meteor_map[i][j] = METEOR_INF;
                }
            }
        }

        // queue push
        queue<P> que;
        // initialize push
        que.push(P(0, 0));
        d[0][0] = 0;

        // bfs loop
        while(que.size()){
            P p = que.front(); que.pop();
            printf("loop %d,%d,%d\n", p.first, p.second, d[p.first][p.second]);
            for(int i = 0; i < 4 ; i++){
                int nx = p.first + dx[i], ny = p.second + dy[i];
                if(0 <= nx && nx < W && 0 <= ny && ny < H && d[nx][ny] != -1 && d[nx][ny] == INF){
                    que.push(P(nx,ny));
                    d[nx][ny] = d[p.first][p.second] + 1;
                    if( d[nx][ny] >= meteor[meteor_index][2]){
                        // printf("debug meteo: %d,%d,%d\n", meteor[meteor_index][0], meteor[meteor_index][1], meteor[meteor_index][2]);
                        if(nx == meteor[meteor_index][0] - 1 || nx == meteor[meteor_index][0] || nx == meteor[meteor_index][0] + 1){
                            if (ny == meteor[meteor_index][1] - 1 || ny == meteor[meteor_index][1] || ny == meteor[meteor_index][1] + 1){
                                printf("meteor! \n");
                                d[ meteor[meteor_index][0] ][ meteor[meteor_index][1] ] = -1;
                                if(1 <= meteor[meteor_index][0]){
                                    d[ meteor[meteor_index][0] -1 ][ meteor[meteor_index][1] ] = -1;
                                }
                                if(meteor[meteor_index][0] < W-1){
                                    d[ meteor[meteor_index][0] +1 ][ meteor[meteor_index][1] ] = -1;
                                }
                                if(1 <= meteor[meteor_index][1]){
                                    d[ meteor[meteor_index][0] ][ meteor[meteor_index][1]-1 ] = -1;
                                }
                                if(meteor[meteor_index][1] < H-1){
                                    d[meteor[ meteor_index][0] ][ meteor[meteor_index][1]+1 ] = -1;
                                }
                                que.pop();
                                meteor_index++;
                            }
                        }
                    }
                }
            }
            if(p.first == meteor[meteor_index][0] - 1 || p.first == meteor[meteor_index][0] || p.first == meteor[meteor_index][0] + 1){
                if (p.second == meteor[meteor_index][1] - 1 || p.second == meteor[meteor_index][1] || p.second == meteor[meteor_index][1] + 1){
                    d[p.first][p.second] = -1;
                }
            }
        }
        int res = -1;
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H ; j++){
                printf("%d,", d[i][j]);
                if(d[i][j] != -1){
                    res = min(max(0, res), d[i][j]);
                }
            }
            printf("\n");
        }
        printf("%d\n",res);
    }
    return 0;
}

