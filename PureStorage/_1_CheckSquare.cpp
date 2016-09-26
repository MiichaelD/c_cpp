/*
  Description:  You have been given 4 points in cartesian plane, and you need to
                determine whether they form a square or not. Can you think of a
                general strategy that works for all types of squares...? Even if 
                the square is not parallel to the X and Y axis.

  Continuation: Suppose you are given N points, how many squares are possible in
                those N points

  For:          Pure Storage

  Programmer:   Michael Duarte

  CoderPad:     https://coderpad.io/6DKDTFX2

  Date:         Sep 23, 2016. 
*/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

struct Point{
  int x, y;
  
  Point(int xx, int yy):x(xx),y(yy){}
  
  int diffX (const Point &p1) const{
    return abs(x - p1.x);
  }
  
  int diffY (const Point &p1) const{
    return abs(y - p1.y);
  }
  
  float getDistanceTo(const Point &p1) const {
    int lenX = diffX(p1);
    int lenY = diffY(p1);
    float len =  sqrt((lenX*lenX) + (lenY*lenY));
    return len;
  }
};

bool isSquare(const vector<Point> &points){
  if (points.size() != 4)
    return false;
  
  // float hypo = -1, side = -1;
  int nextPoint = -1;
  unordered_set<float> distances;
  // comparing point 0 with 1 -> 3. There should be 2 equal lengths and one larger
  for (int i = 1; i < 4; ++i){
    float aux = points[0].getDistanceTo(points[i]);
    if (distances.find(aux) != distances.end()){
      nextPoint = i;
      // uncomment next lines if you want to know the length of one side and the hypotenuse
    //   side = aux;
    // } else if (aux > hypo){
    //   hypo = aux;
    }
    distances.insert(aux);
    if (distances.size() > 2)
      return false;
  }
  
  for (int i = 0; i < 4; ++i){
    if (i == nextPoint) continue;
    float aux = points[nextPoint].getDistanceTo(points[i]);
    distances.insert(aux);
    if (distances.size() > 2)
      return false;
    
  }  
  // cout << "square len : " << side << ". hypotenuse: " << hypo << endl;  
  return true;
}

// To execute C++, please define "int main()"
int main() {
  vector<Point> points;
  
  points.emplace_back(1,1);
  points.emplace_back(1,2);
  points.emplace_back(2,1);
  points.emplace_back(2,2);
  
  bool square = isSquare(points);
  cout << "is square: " << (square?"YES":"NO") << endl;
  return 0;
}

// Suppose you are given N points, how many squares are possible in those N points
int getHowManySquares(const vector<Point> &points){
  // iterating all points from i -> n;
  // int n = points.size();
  // vector<vector<int>> diffVectors(n-1, vector<int>(n-1) );  //- N^2 
  // for (int i = 0; i < n; ++i){
  //   for (int j = 0; j < n; ++j){
  //      if (i != j){
  //       diffVectors[i][j] = diff (points[i], points[j]);
  //     }
  //   }
  // }
  
  return 0;
}