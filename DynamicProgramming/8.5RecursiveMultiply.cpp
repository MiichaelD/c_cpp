/*
	Description:	8.5 Recursive Multiply: Write a recurive function to multiply 2 positive
					integers without using the * operatoor. You can use adition, substraction
					and bit shifting, but you should minimize the use of those operations.

	Programmer:		Michael Duarte

	Date:			Sep 7, 2016.	
*/

#include <iostream>
#include <deque>
#include <memory>

using namespace std;

int multiplyIt(int max, int min){
	int result = 0;
	for (int i = 1; i <= max; ++i){
		result += min;
	}
	return result;
}

// O(s) where s is the smaller number
int multiplyRec(int max, int min){
	if (min == 0)
		return 0;
	return max + multiplyRec(max, min-1);
}

// 8, 7
//	8, 3
//   8, 1
//	 = 8
//  = 16 + 8 = 24
// = 48 + 8 = 56
// O(log(s)) where s is the smaller number
int multiplyIneverThoughtOf(int max, int min){
	if (min == 0) return 0;
	if (min == 1) return max;

	int halfMin = min >> 1; // divide by 2
	int halfProd = multiplyIneverThoughtOf(max, halfMin); // process product of half

	if (min % 2 == 0){
		return halfProd << 1; // multiply by 2
	} else {
		return (halfProd << 1) + max; // multiply by 2 and add max once more.
	}
}

int multiply(int x, int y, int method = 0){
	int minVal = min(x,y);
	int maxVal = max(x,y);

	switch(method){
		case 0:
			return multiplyRec(maxVal, minVal);
		case 1:
			return multiplyIneverThoughtOf(maxVal, minVal);
		default:
			return multiplyIt(maxVal, minVal);
	}
	return -1;
}

int main(){
	int x, y;
	while(true){
		cin >> x >> y;
		if (x == 0 && y == 0)
			break;

		int result = multiply(x, y, 1);
		cout << x << " times " << y << " = " << result << endl; 
	}	
	return 0;
}