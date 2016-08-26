// Draw Line: A monochrome screen is stored as a single array of bytes, allowing
// 8 consecutive pixels to be stored in 1 byte. The screen has width w, where w
// is divisible by 8 (that is, no byte will be split across rows). The height of
// the screen of course can be derived from the length of the array and the width.
// implement a function that draws a horizontal line from (x1, y) to (x2, y).

// #include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <set>
#include <cstdint>
#include <algorithm>

using namespace std;

typedef uint8_t byte;
// http://stackoverflow.com/questions/26239078/use-of-small-integer-with-bits-operator-in-c
// typedef int byte;


void printByte(byte b){
	for(int i = 7 ; i >= 0; --i)
		cout << ((b & (1 << i)) != 0 ? '-':'0');

}

void printScreen(byte screen[], int bytes, int w){
	int bytesPerWidth = w / 8; // how many bytes per line;
	int bytesMinusOne = bytesPerWidth - 1;
	for (int i = 0 ; i < bytes; ++i){
		printByte(screen[i]);
		if(i % bytesPerWidth == bytesMinusOne){
			cout << endl;
		}
	}
	cout << endl;
}


int drawLine(byte screen[], int bytes, int width, int x1, int x2, int y){
	int bytesPerLine = width / 8; // how many bytes per line;
	int screenLength = bytes * 8; // length in pixels

	int startByte = x1 / 8;
	int startOffset = x1 % 8;
	if (startOffset != 0){
		++startByte;
	}

	int endByte = x2 / 8;
	int endOffset = x2 % 8;
	if (endOffset != 7){
		--endByte;
	}

	for(int b = startByte; b <= endByte; ++b)
		screen[bytesPerLine * y + b] = (byte) 0xFF;

	byte leftMask = (byte) 0xFF >> startOffset;
	byte rightMask = (byte) ~((0x0FF) >> (endOffset + 1));


	cout << "startByte = " << startByte << ". offset = " << startOffset;
	cout << ". endByte = " << endByte << ". offset = " << endOffset << endl;    
	cout << "Left Mask = " << leftMask << ": " ;
	printByte(leftMask);
	cout << ". Right Mask = " << rightMask << ": ";
	printByte(rightMask);
	cout << endl;

	if ((x1/8) == (x2/8)){
		screen[bytesPerLine * y + x1/8] |= leftMask & rightMask;
	} else {
		if(startOffset != 0){
			screen[bytesPerLine * y + startByte - 1] |= leftMask;
		} 
		if(endOffset != 7){
			screen[bytesPerLine * y + endByte + 1] |= rightMask;
		}
	}
}

int main() {
	byte screen[64] = {0}; 
	cout << "BEFORE: " << endl;
	printScreen(screen, 64, 32);
	drawLine(screen, 64, 32, 10, 18, 7);
	cout << "AFTER: "<< endl;
	printScreen(screen, 64, 32);
	cout << 0xFF << "\t" << (byte)(0xFF >> 2 ) << "\t" << (byte)(0xFF << 2) << endl; 
	return EXIT_SUCCESS;
}
