/*
    Description:    Program to find all the prime factors from a given number.
                    Also, when more than 2 numbers have been introduced, the greatest
                    common divisor and the least common multiple will be calculated.

                    How are the prime factors, gcm and lcm related?
                    - the gcm of 2 numbers, a and b, is a number which prime factors are factors 
                    of a and b. 
                    i.e. The gcm(12, 24) is 6 bc its prime factors (one 2 and one 3) are also
                    factors of a (two 2 and one 3) and b (three 2 and one 3): 
                        a = 12 : 2 * 2 * 3;
                        b = 24 : 2 * 2 * 2 * 3;
                        gcm = 6: 2 * 3. 

                    - The lcd of 2 numbers, a and b, is an number which prime factors contains
                    all the prime factors of a and b.
                    i.e. The lcm(12, 24) is 24 bc its prime factors(three 2 and one 3) contains
                    at all of a's factors (two 2 and one 3) and all of b's factors (three 2 and one 3)
                        a = 12 : 2 * 2 * 3;
                        b = 24 : 2 * 2 * 2 * 3;
                        lcm =24: 2 * 2 * 2 * 3.

                    Fun fact: lcm(a,b) * gcm(a,b) = a*b.
                    Ok, it wasn't funny.

    Programmer:     Michael Duarte

    Date:           Sep 3, 2016.
*/

#include <iostream>
#include <vector>
#include <cmath> // std::sqrt
#include <numeric> // std::accumulate

using namespace std;

// A function to print all prime factors of a given number n
vector<int> getPrimeFactors(int n){
    vector<int> factors;
    // Print the number of 2s that divide n
    while (n%2 == 0){
        factors.push_back(2);
        n = n/2;
    }
 
    // n must be odd at this point.  So we can skip one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i += 2){
        // While i divides n, print i and divide n
        while (n%i == 0){
            factors.push_back(i);
            n = n/i;
        }
    }
 
    // This condition is to handle the case whien n is a prime number greater than 2
    if (n > 2)
        factors.push_back(n);
    return factors;
}

template<class T>
void printVector(const vector<T> &vec){
    auto it = vec.begin();
    if (it != vec.end()){
        cout << *it;
        for (++it; it != vec.end(); ++it){
            cout << ", " << *it; 
        }
    }
    cout << endl;
}

// greates commond divisor.
template<class T> T gcd(const T &a, const T &b){ 
    return b == 0 ? a : gcd(b, a%b);
}

template<class T>T gcdVec(const vector<T> &vec){
    return std::accumulate(vec.begin(), vec.end(), 1, gcd<T>);
}

// least common multiple.
template<class T> T lcm(const T &a, const T &b){ 
    return a*b/gcd(a,b);
}

template<class T>T lcmVec(const vector<T> &vec){
    return std::accumulate(vec.begin(), vec.end(), 1, lcm<T>);
}


int main(){
    std::ios::sync_with_stdio(false); // http://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
    cin.tie(NULL);

    // cout << gcd(gcd(3,6),12) << "\t" << gcd(gcd(gcd(5,7),9),12) << endl;
    // cout << lcm(lcm(3,6),12) << "\t" << lcm(lcm(lcm(5,7),9),12) << endl;
    // vector<int> numbers = {5,7,9,12};
    // cout << lcmVec(numbers) << endl;

   int num, prevNum = 0;
   while(true){
        cin >> num;
        if (num == 0) break;

        vector<int> factors = getPrimeFactors(num);
        cout << num <<"\tis prime? " << (factors.size() == 1 ? "Yes": "No" ) << ".  Factors: "; 
        printVector(factors);

        if (prevNum != 0){
            cout << "\tGreates Common Divisor\t(" << num << ", " << prevNum << ") = " << gcd(num,prevNum) << endl;
            cout << "\tLeast Common Multiple\t(" << num << ", " << prevNum << ") = " << lcm(num,prevNum) << endl;
        }
        prevNum = num;
   }
    return 0;
}