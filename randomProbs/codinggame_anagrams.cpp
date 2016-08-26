#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
string phrase;
char phrase_c[100];
size_t length;

bool isLetterAtPos(char c, int pos){
    char position = c - 'A'; 
    return c != ' '  && (position % pos) == pos-1;
}
 
void process2nds(){
    deque<char> seconds;
    
    for(const char &c : phrase_c){ 
        if (isLetterAtPos(c,2)){
            seconds.push_back(c);    
        }
    }
    for(int i = 0, j = length; seconds.size() > 1 &&  i < j; ++i, --j ){
        bool found1st = phrase_c[i] == seconds.front();
        bool found2nd = phrase_c[j] == seconds.back();
        if (found1st && found2nd){
            // swap
            phrase_c[j] = phrase_c[i];
            phrase_c[i] = seconds.back();
            //delete from deque
            seconds.pop_front();
            seconds.pop_back();
        } else if (found1st){
            --i;
        } else if(found2nd){
            ++j;
        }
    }
    // phrase = phrase_c;
}

void process3rds(){
    deque<char> deque;
    for(const char &c : phrase_c){
        if (isLetterAtPos(c,3)){
            deque.push_back(c);    
        }
    }
    
    bool isFirst = true;
    for(int i = 0; deque.size() > 1 &&  i < length; ++i){
        if (isLetterAtPos(phrase_c[i],3)){
//            cerr << "changing: " << phrase_c[i] << ", for: " ; 
            if (isFirst){
                phrase_c[i] = deque.back();
                isFirst = false;
            } else {
                phrase_c[i] = deque.front();
                deque.pop_front();
            }
//            cerr << phrase_c[i] << "." << endl; 
        }
    }
}

void process4ths(){
    deque<char> deque;
    
    for(const char &c : phrase_c){
        if (isLetterAtPos(c,4)){
            deque.push_back(c);    
        }
    }
    
    char firstChar;
    if (deque.size()){
        firstChar = deque.front();
    }
    for(int i = 0; deque.size() &&  i < length; ++i){
        if (phrase_c[i] == deque.front()){
            // cerr << "changing: " << phrase_c[i] << ", for: " ; 
            deque.pop_front();
            phrase_c[i] = deque.size() ? deque.front() : firstChar;
            // cerr << phrase_c[i] << "." << endl; 
        }
    }
    phrase = phrase_c;
}

void processLetterCount(){
    vector<int> lengths;
    
    int wordLength = 0, i = 0;
    for (; i < length; ++i){
        if (phrase_c[i] == ' '){
            lengths.push_back(i - wordLength);
            wordLength = i + 1;
        } 
    }
    lengths.push_back(length - wordLength);
    
    i = 0;
    while (lengths.size()){
        wordLength = lengths.back();
        lengths.pop_back();
        
        bool fixed = false;
        for (int count = 0 ; count < wordLength; ++count){
            if (phrase_c[i+count] == ' '){
                phrase_c[i+count] = phrase_c[i+count+1];
                phrase_c[i+count+1] = ' '; 
                fixed = true;
            } 
        }
        if (fixed == false && phrase_c[i+wordLength] != ' '){
            int spaceInd = i+wordLength+1;
            for (; spaceInd < length && phrase_c[spaceInd]!=' '; ++spaceInd){} 
            for(; spaceInd > i+wordLength; --spaceInd){
                phrase_c[spaceInd] = phrase_c[spaceInd-1];
            }
            phrase_c[spaceInd] = ' '; 
        }
        i += (wordLength + 1);
    }
    
    phrase = phrase_c;
}

int main(){
    getline(cin, phrase);
    length = phrase.copy(phrase_c,phrase.length()); // copy string to c_str
    phrase_c[length] = '\0'; // null char at the end
    
    
    cerr << phrase_c << endl;
    process2nds();
    cerr << " 2nds: " << phrase_c << endl;
    process3rds();
    cerr << " 3rds: " << phrase_c << endl;
    process4ths();
    cerr << " 4ths: " << phrase_c << endl;
    processLetterCount();
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << phrase_c << endl;
}