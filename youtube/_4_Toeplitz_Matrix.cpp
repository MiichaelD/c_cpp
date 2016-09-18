/*
	Description:	Validate if the given matrix is a Toeplitz matrix

	Discussion:		- How would you solve this problem if the matrix was so big that
					there can only be 2 rows of it in memory?

					- What if the only rows that are loaded in memory are not  in the same page
					 i.e. having rows: (0,1) (2,3), (4,5) and so on,  but not (1,2), (3,4))
						- If we had enough memory to allocate an extra row we could use it
						to keep track of the last row and compare it in the next iteration.
						This row would be of size row-1, since the first number of a row is always
						ignored. We could update the row while we are validating it.

					- What if there is no enough space to hold the whole extra array?
						- And here is where I went dumb...


	Programmer:		Michael Duarte

	Date:			Sep 12, 2016.	
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>


using namespace std;

typedef vector<vector<int>> Matrix;

void init(Matrix &matrix){
	for (int i = 0; i < matrix.size(); ++i){
		matrix[i][0] = rand() % 100;
	}

	for (int i = 0; i < matrix.back().size(); ++i){
		matrix[0][i] = rand() % 100;
	}

	for (int i = 1; i < matrix.size(); ++i){
		int prevI = i-1;
		for (int j = 1; j < matrix.back().size(); ++j){
			matrix[i][j] = matrix[prevI][j-1];
		}
	}
}

void unToeplitz(Matrix &matrix){
	int i = rand() % matrix.size();
	int j = rand() % matrix.back().size();
	++matrix[i][j];
	cout << "UnToeplitzed it: matrix["<<i<<"]["<<j<<"] = " <<matrix[i][j] << endl; 
}

bool isToeplitz(const Matrix &matrix){
	for (int i = 1; i < matrix.size(); ++i){
		int prevI = i-1;
		for (int j = 1; j < matrix.back().size(); ++j){
			if (matrix[i][j] != matrix[prevI][j-1])
				return false;
		}
	}
	return true;
}

void print(const Matrix &matrix){
	int digits = static_cast<int>(floor(log(matrix.size() * matrix.size())));
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

int main(){
  	srand (time(NULL)); // initialize random seed.
	int size = 5;
	Matrix matrix(size,vector<int>(30));
	init(matrix);
	unToeplitz(matrix);
	print(matrix);
	cout << "Is Toeplitz: " <<(isToeplitz(matrix)?"Yes":"No") << endl; 

	return EXIT_SUCCESS;
}