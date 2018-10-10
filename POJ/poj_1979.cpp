#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAX_N 20
int W;
int H;
char field[MAX_N][MAX_N];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int res;

void dfs(int x, int y){
    field[y][x] = '#';
    res++;
    // cout << x << "," << y << "," << res << endl;
    for(int delta = 0; delta < 4; delta++){
        int nx = x+dx[delta], ny = y+dy[delta];
        // cout << "debug: n" << nx << "," << ny << ","  << endl;
        if(0 <= nx && nx < W && 0 <= ny && ny < H && field[ny][nx] == '.') dfs(nx, ny);
    }
}

int main(){
    while(scanf("%d %d", &W, &H)){
        if(W == 0 && H == 0) break;
        // cout << "width:" << W << ",height:" << H << ",field input" << endl;
        for(int inp = 0; inp < H; inp++){
            scanf("%s", field[inp]);
        }
        res = 0;
        for(int i = 0; i < H; i++){
            for(int j = 0; j < W; j++){
                if(field[i][j] == '@'){
                    // printf("find.\n");
                    dfs(j, i);
                    printf("%d\n", res);
                }
            }
        }
    }
    return 0;
}