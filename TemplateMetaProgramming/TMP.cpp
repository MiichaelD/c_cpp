#include <iostream>
#include <cstdlib>

template<unsigned long n> // general case: the value of
struct Factorial { // Factorial<n> is n times the value of Factorial<n-1> 
	enum { value = n * Factorial<n-1>::value };
};

template<> // special case: the value of Factorial<0> is 1
struct Factorial<0> {
	enum { value = 1 }; 
};


int main(){
    std::cout << "factorial 5: " << Factorial<5>::value << std::endl;
    std::cout << "factorial 6: " << Factorial<6>::value << std::endl;
    std::cout << "factorial 7: " << Factorial<7>::value << std::endl;
    std::cout << "factorial 8: " << Factorial<8>::value << std::endl;
    std::cout << "factorial 9: " << Factorial<9>::value << std::endl;
    std::cout << "factorial 10: " << Factorial<10>::value << std::endl;
    std::cout << "factorial 15: " << Factorial<50>::value << std::endl;
    std::cout << "factorial 20: " << Factorial<20>::value << std::endl;
    std::cout << "factorial 25: " << Factorial<25>::value << std::endl;
    std::cout << "factorial 30: " << Factorial<30>::value << std::endl;
    std::cout << "factorial 35: " << Factorial<35>::value << std::endl;
    return EXIT_SUCCESS;
}