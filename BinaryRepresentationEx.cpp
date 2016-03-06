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

    vector<int>::reverse_iterator it = ret.rbegin();
    while(it != ret.rend()){
        cout << *it;
        ++it;
    }
    return ret;
}

int main(){
    uint16_t val = 1024;
    uint16_t val1 = val & 0x4FF;
    uint16_t val2 = val >> 8;
    cout << val << " = ";
    convert(val);
    cout << ", &0xFF: " << val1 << ", >>8: " << val2<<endl;
    return 0;
}