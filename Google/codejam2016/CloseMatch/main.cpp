

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <cmath>

using namespace std;

string solution(){
    string coders, jammers;
    cin >> coders >> jammers;
    
    stringstream cod, jam;
    char c, j;
    char prevC = '0', prevJ = '0';
    bool last;
    size_t strLen = coders.length() - 1;
    for (int i = 0 ; i <= strLen; ++i){
        last = i == strLen;
        c = coders[i];
        j = jammers[i];
        if (c == j){
            if (c == '?'){
                if (prevC < prevJ){
                    cod << '9';
                    jam << '0';
                } else if (prevC > prevJ){
                    cod << '0';
                    jam << '9';
                } else {
                    cod << '0';
                    jam << '0';
                }
            } else {
                cod << c;
                jam << j;
            }
        } else {
            if (c == '?'){
                cod << static_cast<char>( last ? j-1 : j);
                jam << j;
            } else if (j == '?'){
                cod << c;
                jam << static_cast<char>( last ? c+1 : c);
            } else {
                cod << c;
                jam << j;
            }
        }
        prevC = c;
        prevJ = j;
    }
    
    cod << ' ' << jam.str();
    return cod.str();
}

int main(){
    int  N;
    cin >> N;
    getchar();
    for (int i = 1 ; i <= N; ++i){
        cout << "case #"<<i<<": " << solution() <<endl;
    }
    
}