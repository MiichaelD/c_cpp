

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

const string DIGITS[10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
const string WEIRD_CHARS[10] = {"Z", "ONE", "W", "THREE", "U", "FIVE", "X", "SEVEN", "G", "NINE"};
const int SPECIAL_ORDER[10] = {0, 2, 4, 5, 6, 7, 8, 9, 3, 1};

int m_digitRepetition[10];
int m_differentChars[26];
int m_lettersRead = 0;

inline char letterToIndex(char c){
    return c-'A';
}

void printMissingLetters(){
    cout << "We didn't finish all the letters!!: ";
    for (char m = 0; m < 26; ++m){
        if (m_differentChars[m])
            cout << static_cast<char>('A'+m)<<'('<<m_differentChars[m]<<") ";
    }
}

void removeConsumed(int wordIndex, int amountConsumed){
    if (amountConsumed > 0){
        const string &digitsStr = DIGITS[wordIndex];
        for(int j = 0; j < digitsStr.length(); ++j){ // remove minor amount of repeted letters conforming I
            m_differentChars[letterToIndex(digitsStr[j])] -= amountConsumed;
        }
        
        m_lettersRead -= amountConsumed * digitsStr.length();
        m_digitRepetition[wordIndex] = amountConsumed;
    }
}

void processNumberDigits(int wordIndex){
    int reps = 10000;
    const string &indicators = WEIRD_CHARS[wordIndex];
    for(int j = 0; j < indicators.length(); ++j){ // get amount of letters repeted
        reps = min(m_differentChars[letterToIndex(indicators[j])], reps);
    }
    
    removeConsumed(wordIndex, reps); // remove letters from consumed word
}

void processDigits(){
    for (int i : SPECIAL_ORDER){ // this is the order they should be checked
        if (WEIRD_CHARS[i].length() == 1){ // if it is a number with weird letter, just check that leter
            int reps = m_differentChars[letterToIndex(WEIRD_CHARS[i][0])];
            removeConsumed(i, reps);
        } else { // else check all its letters
            processNumberDigits(i);
        }
    }
}

string getNumberString(){
    stringstream stream;
    for(int i = 0 ; i < 10 ; ++i){
        for (int j = 0; j < m_digitRepetition[i]; ++j){ // print number {repeted} times
            stream << i;
        }
    }
    return stream.str();
}

string solution(){
    memset(m_digitRepetition,0,10 * sizeof(int));
    memset(m_differentChars,0,26 * sizeof(int));
    char c;
    m_lettersRead = 0;
    while((c = getchar()), c != '\n'){
        ++m_differentChars[letterToIndex(c)];
        ++m_lettersRead;
    }
    
    processDigits();
    if (m_lettersRead){
        printMissingLetters();
    }
    
    return getNumberString();
}

int main(){
    int  N;
    cin >> N;
    getchar();
    for (int i = 1 ; i <= N; ++i){
        cout << "case #"<<i<<": " << solution() <<endl;
    }
    
}