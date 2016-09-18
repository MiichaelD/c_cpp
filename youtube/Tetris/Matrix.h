/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/
#include <iostream>
#include <vector>

template<class T>
using Matrix =  std::vector<std::vector<T>>;

template<class T>
Matrix<T> createMatrix(uint32_t size){
	return Matrix<T>(size, std::vector<T>(size));
}

template<class T>
Matrix<T> createMatrix(uint32_t height, uint32_t width){
	return Matrix<T>(height, std::vector<T>(width));
}

template<class T>
void rotateMatrix(std::vector<std::vector<T>> &matrix, bool clockwise = true){
	int rowLimit = matrix.size() / 2;
	int colLimit = matrix.size();
	int dim = matrix.size() - 1;
	if (clockwise == true){
		for (int r = 0 ; r < rowLimit; ++r){
			--colLimit;
			for (int c = r; c < colLimit; ++c){
				T aux = matrix[r][c]; // copy top-left to aux
				matrix[r][c] = matrix[dim-c][r]; // copy bottom-left to top-left
				matrix[dim-c][r] = matrix[dim-r][dim-c]; // copy bottom-right to bottom-left 
				matrix[dim-r][dim-c] = matrix[c][dim-r]; // copy top-right to bottom right
				matrix[c][dim-r] = aux; // copy aux to top-right
			}
		}
	} else {
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
}

template<class T>
void printMatrix(const std::vector<std::vector<T>> &matrix){
	if (matrix.size()){
		for (int r = 0; r < matrix.size(); ++r){
			int colLimit = matrix[r].size();
			for (int c = 0; c < colLimit; ++c){
				std::cout << (c == 0 ? "" : " " ) << matrix[r][c];
			}
			std::cout << std::endl;
		}
	}
}