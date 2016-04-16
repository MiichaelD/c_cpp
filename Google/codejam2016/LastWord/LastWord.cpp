#include <string>
#include <iostream>
#include <deque>

using namespace std;
int main(){
    int N;
    string S;
    cin >> N;
    for (int k = 1; k <= N ; ++k){
        cin >> S;
        deque<char> deque;
        for(int i = 0 ; i < S.length(); ++i){
            char c = S[i];
            
            if (deque.empty()){
                deque.push_back(c);
            } else {
                if ( c < deque.front()){
                    deque.push_back(c);
                } else {
                    deque.push_front(c);
                }
            }
        }
        
        cout << "Case #"<< k << ": ";
        for (char c : deque){
            cout << c;
        }
        cout << endl;
    }
    return 0;
}
