
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

#include <queue>
#include <iostream>
#include <unordered_map>
using namespace std;

/*
 * Complete the function below.
 */


unordered_map<char, queue<unsigned> > patternReps;
unordered_map<char, string > patternMap;
vector<int> lengthLimiter;

 void initMaps(const string &pattern, const string&input){
 	patternReps.clear();
 	patternMap.clear();
    lengthLimiter.clear();
    lengthLimiter.reserve(pattern.length());
 	for(unsigned i = 0; i < pattern.length(); ++i){
        auto &queue = patternReps[pattern[i]];
        queue.push(i);
    }
 }

 int getSubstrRepsInInput(const string &input, const string& substr, size_t &startingPos, size_t &len){
 	cout << "input: "<<substr << "("<<len<<"), starting pos: "<< startingPos+len <<", found at: ";
    int reps = 0;
 	do{
    	startingPos += len;
        int newPos = input.find(substr, startingPos);
        if (newPos == string::npos){
        	break;
        } else {
        	++reps;
        	startingPos = newPos;
        	cout << startingPos << ", ";
    	}
    } while ( (startingPos+len <= input.length()) );
    cout << endl;
    return reps;
 }

void decreasePatternRep(unordered_map<char, queue<unsigned> > &reps, char c){
    auto &repQueue = reps[c];
    repQueue.pop();
    if (repQueue.size() == 0){
        reps.erase(c);
    }
}

void incrementPatternRep(unordered_map<char, queue<unsigned> > &reps, char c, int val = -1){
    auto &repQueue = reps[c];
    repQueue.push(val);
}

bool followsPattern(string &pattern, string &input){
	size_t accumLength = 0;
	//iterate thru each pattern letter to find its corresponding match
    for(unsigned i = 0; i < pattern.length(); ++i){
        // vector keeping track of all the substrings matching a letter from the pattern
        vector<string> matches; 

    	//if there is a match for the letter being checked, prove that it matches
    	const string &section = patternMap[pattern[i]];
    	if (!section.empty()){
    		cout << "checking if " << pattern[i] << " == " << section << endl;
    		for (int t = 0 ; t < section.length() ; ++t){
    			if (section[t] != input[accumLength+t])
    				//there is a descripancy, explode!
                    //TODO: this could restart all the process to get different matches for the pattern
    				return false;
    		}
    		// they match! check next pattern's character.
    		decreasePatternRep(patternReps, pattern[i]);
    		accumLength += section.length();
    		continue;
    	}
    	//Try to find a match for this pattern's character
    	auto &repQueue = patternReps[pattern[i]];

    	//try different string lengths to substring the input and count the amount
    	//of times it is repeated in the input.
    	size_t maxLen = input.length() - accumLength + 1;
    	bool foundMatch = false;
        for (size_t len = 1; len < maxLen; ++len){
            size_t newPos = accumLength-len;
            string substr = input.substr(accumLength, len);
            //count number of times the substring is repeated in the input.
            int reps = getSubstrRepsInInput(input, substr, newPos, len);
            
            if (reps == repQueue.size()){
            	//if the # of reps is the same as the pattern's character amount of reps
            	//we might have found a match!, but let's keep trying to make the substring larger
                matches.push_back(substr);
                cout <<"\t"<<pattern[i] << " possibly: "  << substr << endl;
            } else if (reps < repQueue.size() && !matches.empty() ){
            	//once we start getting not enough repetitions but we once did get enough,
            	//we take the last good substring as the match!
                size_t matchIndex = matches.size() - 1 - lengthLimiter[i];
                if (matchIndex >= matches.size()){
                    cout << "potential substrings: " << matches.size() << " , skipping last " << lengthLimiter[i] <<" options";
                    return 0;  //we ran out of possibilities for this character.
                }

                const string & match = matches[matchIndex];
            	accumLength += match.length();

            	//save the match for future reference.
                patternMap[pattern[i]] = match;

                //decrement the number of times this pattern's char repeated
                //since we just finished matching one.
                decreasePatternRep(patternReps, pattern[i]);

                cout << pattern[i] << " == "  << match <<". Next starting pos: " << accumLength<< endl << endl;
                foundMatch = true;
                break;
            }
        }

        if(!foundMatch){
        	//Not finding a match could mean that this input is not following the pattern
        	//or that one of the precious matches grabbed more characters than it should have.
        	// i.e.
        	// pattern:	 abab
        	// input:		redblueredblue
            // result: a = redbl, b= ue. it works, but not as a human would've solve it.
        	// 1st match would be redblue, which is incorrect
            cout << "Match not found for letter " << pattern[i] << " trying to re-evaluate previous pattern" << endl;
            bool isNotFirstLetterOfPattern = i > 0;
            if (i>0){
                ++lengthLimiter[--i];
                incrementPatternRep(patternReps, pattern[i]); // add another repetition to previous pattern character
                accumLength -= patternMap[pattern[i]].length();
                patternMap.erase(pattern[i]);
                --i; // re-evaluate previous character, we go back 2 index bc we increment at the end of the loop 
            }

        	//TO BE CONTINUED.
        }
    }
    return patternReps.empty()?true:false;
}

bool wordpattern(string &pattern, string &input) {
	initMaps(pattern,input);
    return followsPattern(pattern,input);
}


int main() {
	cout << "Pattern: ";
    string _pattern = "abba";
    // cin >> _pattern;
    
    cout << "Input: ";
    string _input = "redblueredblue";
    // cin >> _input;
    
    cout << "pattern: " << _pattern << ", input: " << _input << ". TEST: " << endl;
    bool ans = wordpattern(_pattern, _input);
    cout << (ans ? 1 : 0) << endl;
    
    return 0;
}