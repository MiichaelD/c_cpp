//
//  main.cpp
//
//  Created by Michael Duarte on 4/25/16.
//  Copyright © 2016 Michael Duarte. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

bool sortData(std::pair<string, int> &lh, std::pair<string,int> &rh){
    return lh.second > rh.second;
}

int main(){
    vector<string> words;
    words.reserve(35000);
    string word;
    
    ifstream inFile;
    inFile.open("corpus.txt");
    while(!inFile.eof()){
        inFile >> word;
        words.emplace_back(std::move(word));
    }
    inFile.close();
    
    int N, A, B;
    cin >> N;
    for (int i = 1; i <= N; ++i){
        cout << "Case #" << i << ": ";
        cin >> A >> B;
        unordered_map<string, int> indexMap;
        vector<std::pair<string,int>> counter;
        for (int i = A-1; i <B; ++i){
            if (indexMap.find(words[i]) == indexMap.end()){
                indexMap[words[i]] = static_cast<int>(counter.size());
                counter.push_back({words[i],1});
            } else {
                ++counter[indexMap.at(words[i])].second;
            }
        }
        sort(counter.begin(), counter.end(), sortData);
        
        auto it = counter.begin();
        cout << it->first << ' ' << it->second;
        for (int i = 1; i < 3; ++i){
            ++it;
            cout << ',' << it->first << ' ' << it->second;
        }
        cout << endl;
    }
    
}