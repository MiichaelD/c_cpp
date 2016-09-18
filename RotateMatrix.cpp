/*
	Description:	Rotate Matrix.

	Programmer:		Michael Duarte

	Date:	     		Sep 12, 2016.	
*/

#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include <vector>
#include <cmath>

using namespace std;

const int DIM = 3;

// = {{1,2,3,4,5},
//    {6,7,8,9,5},
//    {1,2,3,4,5},
//    {1,2,3,4,5},
//    {1,2,3,4,5},}

void fillMatrix(vector<vector<int>> &matrix){
  // matrix.reserve(DIM);
  for(int i = 0 ; i < DIM; ++i){
    matrix[i].reserve(DIM);
    for (int j = 0 ; j < DIM; ++j){
      matrix[i].push_back(i*DIM + j + 1);
    }
  }
}

void printMatrix(const vector<vector<int>> &matrix){
  int digits = static_cast<int>(floor(log(DIM * DIM)));
  for (auto &vec : matrix){
    auto it = vec.begin();
    cout << '[';
    if (it != vec.end()){
      cout << *it;
      for (++it; it != vec.end(); ++it){
        cout << "," << setw(digits) <<*it;
      }
    }
    cout << ']' << endl;
  }
  cout << endl;
}

template<class T>
void rotateMatrix(vector<vector<T>> &matrix, bool clockwise = true){
  int rowLimit = DIM / 2;
  int colLimit = DIM;
  int dim = DIM - 1;
  if (clockwise)
    for (int r = 0 ; r < rowLimit; ++r){
      --colLimit;
      for (int c = r; c < colLimit; ++c){
        T aux = matrix[r][c]; // copy top-left to aux
        matrix[r][c] = matrix[dim-c][r]; // copy bottom-left to top-left
        matrix[dim-c][r] = matrix[dim-r][dim-c]; // copy bottom-right to bottom-left 
        matrix[dim-r][dim-c] = matrix[c][dim-r]; // copy top-right to bottom right
        matrix[c][dim-r] = aux; // copy aux to top-right
      }
      // cout << "At Step: " << (r+1) << endl;
      // printMatrix(matrix);
    }
  else 
    for (int r = 0 ; r < rowLimit; ++r){
      --colLimit;
      for (int c = r; c < colLimit; ++c){
        T aux = matrix[r][c]; // copy top-left to aux
        matrix[r][c] = matrix[c][dim-r];//copy top-right to top-left 
        matrix[c][dim-r] = matrix[dim-r][dim-c];//copy bottom-right to top-right
        matrix[dim-r][dim-c] = matrix[dim-c][r]; //copy bottom-left to bottom-right
        matrix[dim-c][r] = aux; // copy aux to bottom-left
      }
    }
}




int main(){
  vector<vector<int>> matrix(DIM);
  fillMatrix(matrix);
  printMatrix(matrix);
  cout << "Rotated:" << endl;
  bool clockWise = false;
  rotateMatrix(matrix, clockWise);
  printMatrix(matrix);
	return EXIT_SUCCESS;
}