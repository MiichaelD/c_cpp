/* 
		Create a function drawHtree(); to draw a tree like: 
		https://en.wikipedia.org/wiki/H_tree#/media/File:H_tree.svg

		Given Length is for the horizontal line, the vertical lines have a length of ( Length/sqrt(2) );

		drawLine 

*/
#include <cmath>

const float SQRT_OF_TWO = sqrt

struct Point {
	float x,y
};

void drawLine(const Point &start, const Point &end);

void drawHTree(Point center, float length, int depth){
	if (depth-- == 0) return;

	float halfLength = length/2;
	float verticalLength = length / SQRT_OF_TWO;
	float halfVerticalLength = verticalLength / 2;

	// draw horizontal line
	Point pointA{center.x - halftLength, center.y};
	Point pointB{center.x + halftLength, center.y};
	drawLine(pointA,pointB);

	// draw left vertical line
	pointA.y -=halfVerticalLength; 			// top left
	pointB.x = pointA.x;					// bottom left
	pointB.y += halfVerticalLength;
	drawLine(pointA,pointB);
	//and its h trees (if any) recursively
	drawHTree(pointA, verticalLength / SQRT_OF_TWO, depth);
	drawHTree(pointB, verticalLength / SQRT_OF_TWO, depth);

	//draw left vertical line
	pointA.x += length;
	pointB.x += length;
	drawLine(pointA,pointB);
	//and its h trees (if any) recursively
	drawHTree(pointA, verticalLength / SQRT_OF_TWO, depth);
	drawHTree(pointB, verticalLength / SQRT_OF_TWO, depth);
}