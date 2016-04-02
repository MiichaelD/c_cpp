
/**
	You're given two strings, "pattern" and "input", e.g.
 
 pattern: "abba"
 input: "redbluebluered"
 
 This example is considered a match because the pattern of words in input matches the pattern of characters in pattern.
 The pattern specifies that you have an instance of one word, two instances of another word, and another instance
 ofthe first word.
 
 Write a function that takes in a pattern and an input, and determines whether you have a match.
 Return 1 if it is a match, and 0 if it is not a match.
 
 The running time of the algorithm is exponential to the length of the input. Performance isn't too important for this
 question, but the algorithm should be efficient enough to run the provided test cases.
 
 The pattern can contain any characters in any order.
 
 Words must be at least one character long.  The input will be at least as long as the pattern.
 
 Distinct pattern characters must correspond to distinct input words, so e.g. A pattern of "abba" and an input of
 "redredredred" is NOT a match.
 
 SAMPLE CASES:
 1) pattern is "abba", input is "redbluebluered" - should return 1
 2) pattern is "aaaa", input is "redbluebluered" - should return 0
 
 NOTE: The input does not need to contain actual "dictionary words". "abcxyzxyzabc" would also be an input that matches the pattern "abba".
 */

#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

struct PatternInfo{
    char character;
    int repetitions;
    stack<string> tentativeMatches;
    
    void clearProgress(){
        while(tentativeMatches.size())
            tentativeMatches.pop();
    }
    
    bool trySmallerSubstring(){
        if (tentativeMatches.size() < 2 )
            return false;
        
        // we are gonna re-evaluate this pattern character
        tentativeMatches.pop();  // with a smaller substring
        ++repetitions;  // we have to fin another repetition
        return true;
    }
    
    inline bool hasTentativeMatches() const{ return tentativeMatches.size();}
    
    /* Check if there are tentative matches before trying to get one */
    inline const string &getTentativeMatch() const{ return tentativeMatches.top(); }
};

unordered_map<char, PatternInfo> m_data; // data owner

void initMaps(const string &pattern, const string&input){
    m_data.clear();
    for(unsigned i = 0; i < pattern.length(); ++i){
        auto &info = m_data[pattern[i]];
        info.character = pattern[i];
        ++info.repetitions;
    }
}

int getSubstrRepsInInput(const string &input, const string& substr, size_t startingPos){
    // cout << "input: "<<substr << "("<<len<<"), starting pos: "<< startingPos+len <<", found at: ";
    int reps = 0;
    size_t substrLen = substr.length();
    do{
        startingPos += substrLen;
        size_t newPos = input.find(substr, startingPos);
        if (newPos == string::npos){
            break;
        } else {
            ++reps;
            startingPos = newPos;
            // cout << startingPos << ", ";
        }
    } while ( (startingPos+substrLen <= input.length()) );
//    cout << endl;
    return reps;
}

bool tryCorrectingLastMatch(size_t &patternIndex, size_t &startPoint, const string &pattern){
    char previousChar = pattern[patternIndex - 1];
    auto &info = m_data[previousChar];
    if (patternIndex == 0 || !info.hasTentativeMatches()){
        // if we cannot find a match for the first letter, we are done.
        return false;
    }
    for (size_t i = patternIndex ; i < pattern.length() ;++i )
        if (pattern[i] != previousChar)
            m_data[pattern[i]].clearProgress(); // restart the progress from current index on.
    
    
    size_t lastMatchLen = info.getTentativeMatch().length();
    if(!info.trySmallerSubstring())
        return false;
    startPoint -= lastMatchLen;  // subtract the match's length to the starting point.
    patternIndex -= 2;  // re-evaluate previous character, we go back 2 index bc we increment at the end of the loop
    return true;
}

bool followsPattern(string &pattern, string &input){
    size_t accumLength = 0;
    //iterate thru each pattern letter to find its corresponding match
    for(size_t i = 0; i < pattern.length(); ++i){
        char currentChar = pattern[i];
        auto &info = m_data[currentChar];
        //if there is a match for the letter being checked, prove that it matches
        if (info.hasTentativeMatches()){
            const string &match = info.getTentativeMatch();
//            cout <<"checking if "<< currentChar <<" == "<< match;
            bool didMatch = true;
            for (int t = 0 ; t < match.length() && accumLength+t < input.length(); ++t){
                if (match[t] != input[accumLength+t]){
                    //there is a descripancy, explode... or try fixing it.
                    didMatch = false;
                    if (tryCorrectingLastMatch(i, accumLength, pattern))
                        break;
                    else
                        return false;
                }
            }
            
//            cout << (didMatch?" YESS":" no :(")<<endl;
            
            if(didMatch){
                // they match! check next pattern's character.
                --info.repetitions;
                accumLength += match.length();
            }
            continue;
        }
        
        // Find a match for this pattern's character, try different string lengths to substring the input and
        // count the amount of times it is repeated in the input.
        size_t maxLen = input.length() - accumLength + 1;
        bool foundMatch = false;
        for (size_t len = 1; len < maxLen; ++len){
            size_t newPos = accumLength-len;
            string substr = input.substr(accumLength, len);
            //count number of times the substring is repeated in the input.
            int reps = getSubstrRepsInInput(input, substr, newPos);
            
            if (reps == info.repetitions){
                //if the # of reps is the same as the pattern's character amount of reps
                //we might have found a match!, but let's keep trying to make the substring larger
                info.tentativeMatches.push(substr);
//                cout <<"\t'"<< currentChar <<"' possibly: "<< substr <<endl;
                
                // do not consume all the characters, leave at least as many as remaining characters in the pattern
                if ((maxLen-len-1 >= pattern.length() - i))
                    continue;
            }
            
            if ( reps <= info.repetitions){
                //once we start getting not enough repetitions but we once did get enough,
                //we take the last good substring as the match!
                if (info.hasTentativeMatches()){
                    //decrement the number of times this pattern's char repeated since we just finished matching one.
                    --info.repetitions;
                    accumLength += info.getTentativeMatch().length();
//                    cout << currentChar <<" == "<< info.getTentativeMatch() <<". Next starting pos: "<< accumLength<<endl<<endl;
                    foundMatch = true;
                }
                break;
            }
        }
        
        if(!foundMatch){
            //Not finding a match could mean that this input is not following the pattern
            //or that one of the precious matches grabbed more characters than it should have.
            // i.e. pattern: abab, input: redblueredblue -->> result: a = redbl, b= ue. it works, but not as a human would've solve it.
//            cout << "Match not found for letter " << pattern[i] << " trying to re-evaluate previous pattern" << endl;
            if (!tryCorrectingLastMatch(i, accumLength, pattern))
                return false;
        }
    }
    return true;
}

bool wordpattern(string &pattern, string &input) {
    initMaps(pattern,input);
    return followsPattern(pattern,input);
}

int main() {
    // abba - redblueredblue = NO
    // abba - redbluebluered = OK
    // abab - redblueredblue = OK
    // abb  - redblueblue = OK
    cout << "Pattern: ";
    string _pattern = "abab";
    // cin >> _pattern;
    
    cout << "Input: ";
    string _input = "redblueredblue";
    // cin >> _input;
    
    cout << "pattern: " << _pattern << ", input: " << _input << endl;
    bool ans = wordpattern(_pattern, _input);
    cout << (ans ? 1 : 0) << endl;
    return 0;
}
