//
//  Hadouken.cpp
//
//  Created by Michael Duarte on 4/25/16.
//  Copyright © 2016 Michael Duarte. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

static const string R = "R";
static const string RU = "RU";
static const string RD = "RD";
static const string D = "D";
static const string U = "U";
static const string L = "L";
static const string LU = "LU";
static const string LD = "LD";
static const string K = "K";
static const string P = "P";


static const string COMBOS[5] = {"L-LD-D-RD-R-P", "D-RD-R-P", "R-D-RD-P",
                                 "D-LD-L-K", "R-RD-D-LD-L-K"};

typedef list<string const * const> combos_list;

enum class RESULT {EMPTY = 0, FOUND = 1, IN_PROGRESS, FOUND_IN_PROGRESS };

static const unordered_map<char, combos_list> startsWith {{'L',{&COMBOS[0]}},
    {'D',{&COMBOS[1], &COMBOS[3]}}, {'R',{&COMBOS[4], &COMBOS[2]}} };

struct PossibleCombo{
    combos_list combos;
    int index = 0;
    
    PossibleCombo(const combos_list &vector): combos(vector){}
    
    RESULT processCharacter(char c){
        RESULT rs = RESULT::IN_PROGRESS;
        auto it = combos.begin();
        for (; it != combos.end();){
            string const * const comboStr = *it;
            char currChar = comboStr->at(index);
            int diff = static_cast<int>(comboStr->length() - index);
            if (c == '\n' && currChar == '-'){ // input string finished, but combo didn't
                // check if we missed only one move by not finding any other dash
                bool dashFound = false;
                for (int i = index+1; i < comboStr->length(); ++i ){
                    if ( comboStr->at(i) == '-'){
                        dashFound = true;
                        break;
                    }
                    if (!dashFound){
                        // we only missed last move!
                        rs = RESULT::FOUND;
                        it = combos.erase(it);
                    }
                }
                
            } else if (diff > 1){ // in progress
                if (currChar != c){
                    // combo interrupted by other character;
                    it = combos.erase(it);
                } else {
                    // if not interrupted, we still in the game.
                    ++it;
                }
            } else if (diff == 1){ // check if last character is different;
                if (currChar != c){
                    rs = RESULT::FOUND;
                }
                // this combo was completed, remove it.
                it = combos.erase(it);
            } else {
                // if we reached the end, this combo was completed
                cerr << "\tThis should NOT be happening!!" << endl;
            }
        }
        ++index;
        if (combos.empty()){
            if (rs == RESULT::IN_PROGRESS)// no combos matched
                rs = RESULT::EMPTY;
        } else if (rs == RESULT::FOUND){
            // At least 1 combo matched but there are some others that could be matched too
            rs = RESULT::FOUND_IN_PROGRESS;
        }
        return rs;
    }
};

int getMissedComboCount(){
    char c;
    list<PossibleCombo> possibleCombos;
    int result = 0;
    cout << "\t\t\t";
    while (true){
        c = getchar();
        cout << c;
        int previousResult = result;
        
        if (startsWith.find(c) != startsWith.end()){
            const combos_list &newCombos = startsWith.at(c);
            possibleCombos.emplace_back(newCombos);
        }
        
        auto it = possibleCombos.begin();
        for (;it != possibleCombos.end();){
            switch(it->processCharacter(c)){
                case RESULT::FOUND_IN_PROGRESS: // we found a match, but there could be more, don't delete
                    if (previousResult == result)
                        ++result;
                    ++it;
                    break;
                case RESULT::FOUND: // found match and no combos left, delete
                    if (previousResult == result)
                        ++result;
                case RESULT::EMPTY: // no combols left, delete
                    it = possibleCombos.erase(it);
                    break;
                case RESULT::IN_PROGRESS: // in progress, check next one.
                default:
                    ++it;
                    break;
            }
        }
        
        if (c == '\n') // end of line
            break;
    }
    return result;
}

int main(){
    int N;
    cin >> N;
    getchar(); // consume new line char;
    for (int i = 1; i <= N; ++i){
        int missedCombos = getMissedComboCount();
        cout << "Case #" << i << ": "<<missedCombos<<endl;
    }
    return EXIT_SUCCESS;
}
