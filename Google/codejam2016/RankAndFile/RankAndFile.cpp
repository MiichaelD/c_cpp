#include <iostream>
#include <unordered_map>

/**
1
3
1 2 3
2 3 5
3 5 6
2 3 4
1 2 3


 */
using namespace std;
const int MAX_N = 50;

int main(){
    int T, N;
    cin >> T;
    for (int k = 1; k <= T ; ++k){
        cin >> N;
        unordered_map<int, int> reps;
        int lines = 2*N - 1;
        int n;
        for(int i = 0 ; i < lines; ++i){
            for (int j = 0; j < N; ++j){
                cin >> n;
                if (reps.find(n) == reps.end())
                    reps[n] = 1;
                else {
                    ++reps[n];
                }
            }
        }
        
        int arr[N];
        int index = 0;
        cout << "Case #"<< k << ": ";
        for (auto tuple :reps){
            if (tuple.second % 2 != 0)
                arr[index++] = tuple.first;
        }
        
        sort(arr, arr+N);
        
        for (int i = 0 ; i < N ; ++ i)
            cout << arr[i] << ((i == N-1) ? "":" ");
        cout << endl;
       
    }
    return 0;
}
