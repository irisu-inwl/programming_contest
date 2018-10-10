#include <iostream>
#include <cstdio>
#include <string.h>
#include <string>
#include <map>

using namespace std;

char s[128];
int n;
char phone_number[64];
char access_table[128];
map<string, int>::iterator itr;

int main(){
    access_table['A'] = access_table['B'] = access_table['C'] = '2';
    access_table['D'] = access_table['E'] = access_table['F'] = '3';
    access_table['G'] = access_table['H'] = access_table['I'] = '4';
    access_table['J'] = access_table['K'] = access_table['L'] = '5';
    access_table['M'] = access_table['N'] = access_table['O'] = '6';
    access_table['P'] = access_table['R'] = access_table['S'] = '7';
    access_table['T'] = access_table['U'] = access_table['V'] = '8';
    access_table['W'] = access_table['X'] = access_table['Y'] = '9';
    access_table['0'] = '0', access_table['1'] = '1', access_table['2'] = '2', access_table['3'] = '3', access_table['4'] = '4', access_table['5'] = '5', access_table['6'] = '6', access_table['7'] = '7', access_table['8'] = '8', access_table['9'] = '9';

    while(scanf("%d", &n) == 1){
        map<string, int> phone_map;
        for(int inp = 0 ; inp < n; inp++) {
            scanf("%s", s);
            int phone_itr = 0;
            for(int i = 0 ; s[i] ; i++){
                if(s[i] != '-'){
                    phone_number[phone_itr] = access_table[s[i]];
                    phone_itr++;
                    if(phone_itr == 3){
                        phone_number[phone_itr++] = '-';
                    }
                }
            }
            
            phone_number[8] = 0;
            phone_map[phone_number] += 1;
        }
        
        bool dup = false;
        for(itr = phone_map.begin(); itr != phone_map.end(); ++itr){
            if(itr->second > 1){
                dup = true;
                printf("%s %d\n", itr->first.c_str(), itr->second);
            }
        }
        if (!dup){
            printf("No duplicates.");

        }
    }
    return 0;
}