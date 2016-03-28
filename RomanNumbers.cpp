#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 *You are given 2 expressions representing 2 numbers written in roman numerals.
You have to provide the result of the sum of these 2 numbers, also in roman numerals.

I has a value of 1 (maximum 3 in a row)
V has a value of 5 (maximum 1 in a row)
X has a value of 10 (maximum 3 in a row)
L has a value of 50 (maximum 1 in a row)
C has a value of 100 (maximum 3 in a row)
D has a value of 500 (maximum 1 in a row)
M has a value of 1000 (maximum 4 in a row)

The character I just before an V or X has a value of -1 (example IX equals 9)
The character X just before an L or C has a value of -10 (example XL equals 40)
The character C just before an D or M has a value of -100 (example CM equals 900)


 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
unordered_map<char, int> ROMAN_MAP = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

int MAX_CONSTANTS = 7;
string ROMAN_CONSTANTS[] = {"I", "V", "X", "L", "C", "D", "M"};
char ROMAN_CONSTANTS2[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int ROMAN_MULTIPLIERS[] = {1, 5, 10, 50, 100, 500, 1000};

int charToInt(const char *str, int &i, size_t length){
	char c = str[i];
	unsigned int negSum = 0;
	if (i < length-1){
		char nextChar = str[i+1];
		if (c == 'I' && (nextChar == 'V' || nextChar == 'X') ){
			negSum = 1;
		} else if (c == 'X' && (nextChar == 'L' || nextChar == 'C')){
			negSum = 10;
		} else if (c == 'C' && (nextChar == 'D' || nextChar == 'M')){
			negSum = 100;
		} 

		if(negSum > 0 ){ 
			++i;
			c = nextChar;
		}
	}
	auto tuple = ROMAN_MAP.find (c);
    int val = tuple == ROMAN_MAP.end() ? 0 : tuple->second;
    return val - negSum;
} 
 
 
int romanToDecimal(const string roman){
    const char *str = roman.c_str();
    size_t length = roman.length();
    int accum = 0;
    for(int i = 0; i < length; ++i){
        accum += charToInt(str, i, length);
    }
    return accum;
}

string decimalToRoman(int dec){
    string roman;
    int i = MAX_CONSTANTS - 1;
    for (;i>=0 && dec > 0 ; --i){
        size_t division = dec / ROMAN_MULTIPLIERS[i];
        if (division > 0){
        	if ( dec == 4){
            	roman.append("IV");
            	dec -= 4;
        	} else if (dec == 9){
				roman.append("IX");	
				dec -= 9;
        	} else if (dec > 39  && dec < 50){
				roman.append("XL");	
        		dec -= 40;
        	}else if (dec > 89 && dec < 100){
				roman.append("XC");	
        		dec -= 90;
        	} else if (dec > 399 && dec< 500){
        		roman.append("CD");
        		dec -= 400;
        	} else if (dec > 899 && dec < 1000){
        		roman.append("CM");
        		dec -= 900;
        	} else{
        		dec %= ROMAN_MULTIPLIERS[i];
            	roman.append(division, ROMAN_CONSTANTS2[i]);
        	}
        }
    }
    return roman;
}
 
int main()
{
    string rom1;
    cin >> rom1; cin.ignore();
    string rom2;
    cin >> rom2; cin.ignore();
    
    int val1 = romanToDecimal(rom1);
    int val2 = romanToDecimal(rom2);
    int value = val1 + val2;
    cout << "sum = " << value << endl;
    string roman = decimalToRoman(value);
    cout << roman << endl;
    
}