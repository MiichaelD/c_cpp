//
//  TeamLunch.cpp
//  test
//
//  Created by Michael Duarte on 4/25/16.
//  Copyright © 2016 Michael Duarte. All rights reserved.
//

#include <iostream>
#include <cmath>

uint16_t numTables(uint16_t diners){
    if (diners == 0)
        return 0;
    if (diners < 4)
        return 1;
    diners -= 2;
    diners = static_cast<uint16_t>(ceil(static_cast<float>(diners) / 2));
    return diners;
}

int main(){
    using namespace std;
    int T;
    uint16_t diners;
    cin >> T;
    for (int i = 1; i <= T; ++i){
        cin >> diners;
        cout << "Case #"<< i << ": " << numTables(diners) <<endl;    
    }
    return 0;
}