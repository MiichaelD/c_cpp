#include <iostream> 
#include <string>
#include <inttypes.h> // PRIXPTR

using namespace std;

// A meta-function that return the type T if Condition is true.
template <bool Condition, typename T = void>
struct EnableIf {};

template <typename T>
struct EnableIf<true, T> {
  typedef T type;
};

// A meta-function that returns true if both typenames are of the same type
template <typename T, typename U>
struct IsSame {
  static const bool value = false;
};

template <typename T>
struct IsSame<T, T> {
  static const bool value = true;
};

int main(){
	int x = 5;
	int y = 10;
	IsSame<decltype(x), decltype(y)> same;
	cout << "is Same : "<< same.value << endl;
	cout << "is Same : "<< IsSame<int, float>::value << endl<<endl;

	EnableIf<IsSame<float, float>::value, float>::type val = 5.5f;
	cout << "enableIf : " << val << endl;
}