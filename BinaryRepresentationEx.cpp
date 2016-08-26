#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> convert(int x) {
    vector<int> ret;
    while(x) {
        ret.push_back(x&1);
        x>>=1;  
    }
    return ret;
}

void printBinaryVector(const vector<int> &vec){
    vector<int>::const_reverse_iterator it = vec.rbegin();
    while(it != vec.rend()){
        cout << *it;
        ++it;
    }
}

int main(){
    uint16_t val = 1024;
    uint16_t val1 = val & 0x4FF;
    uint16_t val2 = val >> 8;
    cout << val << " = ";
    printBinaryVector(convert(val));
    cout << ", &0x4FF: " << val1 << ", >>8: " << val2<<endl;
    return 0;
}