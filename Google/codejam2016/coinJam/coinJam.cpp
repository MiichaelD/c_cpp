/**

Name:       C) Coin Jam

-NOTE-:       This program only works with small data set (N <= 16); bc numbers with over 16 digits might not be
            represented correctly in the Base array, in the java version of this solution, it works bc I used
            big integers. but it is still reaaaally slooooow, I guess there should be another way to solve this.

Problem:    A jamcoin is a string of N ≥ 2 digits with the following properties:

-Every digit is either 0 or 1.
-The first digit is 1 and the last digit is 1.
-If you interpret the string in any base between 2 and 10, inclusive, the resulting number is not prime.

Not every string of 0s and 1s is a jamcoin. For example, 101 is not a jamcoin; its interpretation in base
2 is 5, which is prime. But the string 1001 is a jamcoin: in bases 2 through 10, its interpretation is 9,
28, 65, 126, 217, 344, 513, 730, and 1001, respectively, and none of those is prime.

We hear that there may be communities that use jamcoins as a form of currency. When sending someone a jamcoin,
it is polite to prove that the jamcoin is legitimate by including a nontrivial divisor of that jamcoin's
interpretation in each base from 2 to 10. (A nontrivial divisor for a positive integer K is some positive
integer other than 1 or K that evenly divides K.) For convenience, these divisors must be expressed in base 10.

For example, for the jamcoin 1001 mentioned above, a possible set of nontrivial divisors for the base 2
through 10 interpretations of the jamcoin would be: 3, 7, 5, 6, 31, 8, 27, 5, and 77, respectively.

Can you produce J different jamcoins of length N, along with proof that they are legitimate?


Input:      The first line of the input gives the number of test cases, T. T test cases follow; each 
    consists of one line with two integers N and J.


Output:     For each test case, output J+1 lines. The first line must consist of only Case #x:, where
    x is the test case number (starting from 1). Each of the last J lines must consist of a jamcoin of
    length N followed by nine integers. The i-th of those nine integers (counting starting from 1) must
    be a nontrivial divisor of the jamcoin when the jamcoin is interpreted in base i+1.

    All of these jamcoins must be different. You cannot submit the same jamcoin in two different lines,
    even if you use a different set of divisors each time.

Limits:     T = 1. (There will be only one test case.)
    It is guaranteed that at least J distinct jamcoins of length N exist.

Small:      N = 16, J = 50

Big:        N = 32, J = 500

Sample:
Input:
1
6 3

Output:
Case #1:
100011 5 13 147 31 43 1121 73 77 629
111111 21 26 105 1302 217 1032 513 13286 10101
111001 3 88 5 1938 7 208 3 20 11


Explanation:     for ease of explanation. Note that this sample case would not appear in either the Small
    or Large datasets.

    This is only one of multiple valid solutions. Other sets of jamcoins could have been used, and there
    are many other possible sets of nontrivial base 10 divisors. Some notes:

    - 110111 could not have been included in the output because, for example, it is 337 if interpreted in
    base 3 (1*243 + 1*81 + 0*27 + 1*9 + 1*3 + 1*1), and 337 is prime.
    - 010101 could not have been included in the output even though 10101 is a jamcoin, because jamcoins
    begin with 1.
    - 101010 could not have been included in the output, because jamcoins end with 1.
    - 110011 is another jamcoin that could have also been used in the output, but could not have been
    added to the end of this output, since the output must contain exactly J examples.
    - For the first jamcoin in the sample output, the first number after 100011 could not have been either
    1 or 35, because those are trivial divisors of 35 (100011 in base 2).

 */
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const uint64_t BASE[11][32] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648},
{1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489, 1162261467, 3486784401, 10460353203, 31381059609, 94143178827, 282429536481, 847288609443, 2541865828329, 7625597484987, 22876792454961, 68630377364883, 205891132094649, 617673396283947},
{1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824, 4294967296, 17179869184, 68719476736, 274877906944, 1099511627776, 4398046511104, 17592186044416, 70368744177664, 281474976710656, 1125899906842624, 4503599627370496, 18014398509481984, 72057594037927936, 288230376151711744, 1152921504606846976, 4611686018427387904},
{1, 5, 25, 125, 625, 3125, 15625, 78125, 390625, 1953125, 9765625, 48828125, 244140625, 1220703125, 6103515625, 30517578125, 152587890625, 762939453125, 3814697265625, 19073486328125, 95367431640625, 476837158203125, 2384185791015625, 11920928955078125, 59604644775390625, 298023223876953125, 1490116119384765625, 7450580596923828125, 359414837200037393, 1797074186000186965, 8985370930000934825, 8033366502585570893},
{1, 6, 36, 216, 1296, 7776, 46656, 279936, 1679616, 10077696, 60466176, 362797056, 2176782336, 13060694016, 78364164096, 470184984576, 2821109907456, 16926659444736, 101559956668416, 609359740010496, 3656158440062976, 21936950640377856, 131621703842267136, 789730223053602816, 4738381338321616896, 9983543956220149760, 4561031516192243712, 8919445023443910656, 16623181993244360704, 7505371590918406144, 8138741398091333632, 11938960241128898560},
{1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607, 282475249, 1977326743, 13841287201, 96889010407, 678223072849, 4747561509943, 33232930569601, 232630513987207, 1628413597910449, 11398895185373143, 79792266297612001, 558545864083284007, 3909821048582988049, 8922003266371364727, 7113790643470898241, 12903046356877184455, 16534348203302084721, 5059972980857283351, 16973066792291431841, 8131003103782713191, 1576789505350337489, 11037526537452362423},
{1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728, 1073741824, 8589934592, 68719476736, 549755813888, 4398046511104, 35184372088832, 281474976710656, 2251799813685248, 18014398509481984, 144115188075855872, 1152921504606846976, 9223372036854775808, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 9, 81, 729, 6561, 59049, 531441, 4782969, 43046721, 387420489, 3486784401, 31381059609, 282429536481, 2541865828329, 22876792454961, 205891132094649, 1853020188851841, 16677181699666569, 150094635296999121, 1350851717672992089, 12157665459056928801, 17185268762964601129, 7093466277004997233, 8500964271916320249, 2721702152408675777, 6048575297968530377, 17543689534297670161, 10319253219002618521, 639558602475808609, 5756027422282277481, 14910758653121394097, 5069619362125685561},
{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000, 10000000000000000000, 7766279631452241920, 3875820019684212736, 1864712049423024128, 200376420520689664, 2003764205206896640, 1590897978359414784, 15908979783594147840, 11515845246265065472, 4477988020393345024, 7886392056514347008, 5076944270305263616, 13875954555633532928} };

void printBaseArrays(){
    int T = 10;
    //    cin >> T;
    int maxN = 32;
    for(int i = 2; i <= T; ++i){
        cout << "final BigInteger base" << i << '['<<maxN<<"] = {";
        uint64_t multiplier = 1;
        for(int o = 0 ; o < maxN; ++o){
            cout << multiplier << (o == maxN-1 ?"":", ");
            multiplier*=i;
        }
        cout << "};"<<endl<<endl;;
    }
}

string intToBinary(size_t input, int max){
    ostringstream out;
    out << 1;
    
    for (int i = max-1; i >= 0; --i){
        if ( input >= BASE[2][i]){
            input%=BASE[2][i];
            out << 1 ;
        } else {
            out << 0;
        }
    }

    out << 1;
    return out.str();
}

uint64_t stringToBase(int baseN, const string &input){
    size_t len = input.size();
    uint64_t out = 0;
    for (size_t i = 0 ; i < len; ++i){
        if (input[i] == '1')
            out += BASE[baseN][len-i-1];
    }
    return out;
}

uint64_t mysqrt (uint64_t a) {
    uint64_t min=0;
    uint64_t max=((uint64_t) 1) << 32;
    while(1) {
        if (max <= 1 + min)
            return min;
        
        uint64_t sqt = min + (max - min)/2;
        uint64_t sq = sqt*sqt;
        
        if (sq == a)
            return sqt;
        
        if (sq > a)
            max = sqt;
        else
            min = sqt;
    }
    return 0;
}


bool isPrime(uint64_t num){
    if (num <= 1)
        return false;
    if (num <= 3)
        return true;
    float numSqrt = sqrt(static_cast<double>(num));
    for (int i = 2; i < numSqrt; ++i){
        if ( num % i == 0){
            return false;
        }
    }
    return true;
}

uint64_t getPrimeFactor(uint64_t num){
    if (num <= 3)
        return 0;
    uint64_t numSqrt = mysqrt(num);
    uint64_t factor = 0;
    for (uint64_t i = 2; i <= numSqrt; ++i){
        if ( num % i == 0){
            return i;
        }
    }
    return factor;
}

void printPrimeFactors(uint64_t num){
    double numSqrt = sqrt(static_cast<double>(num));
    for (int i = 2; i <= numSqrt; ++i){
        if ( num % i == 0){
            cout  << i << " ";
        }
    }
}

void doTheMagic(int N, int J){
    int variableBits = N-2;
    uint64_t posibilities = BASE[2][N-2];
    for (size_t i = 0; i < posibilities && J; ++i){
        string str = intToBinary(i, variableBits);
        bool primeFound = false;
        ostringstream out;
        out << str;
        for (int base =2; base < 11; ++base){
            uint64_t num = stringToBase(base, str);
            uint64_t factor = getPrimeFactor(num);
            if (factor == 0){
                primeFound = true;
                break;
            }
            out << ' ' << factor ;
        }
        if (primeFound)
            continue;
        else {
            cout << out.str() << endl;
            --J;
        }
    }
}


int main() {
    int T, length, outputs;
    cin >> T;
    for(int i = 1; i <= T; ++i){
        cin >> length >> outputs;
        cout << "Case #" << i <<':' << endl;
        doTheMagic(length, outputs);
    }
//    printBaseArrays();
    return 0;
}