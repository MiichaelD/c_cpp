/**

Name:       C) Coin Jam

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
    import java.util.*;
import java.math.BigInteger;
public class CoinJam {

	final static BigInteger BASE[][] = {
			{new BigInteger("1"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0"), new BigInteger("0")},
			{new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1"), new BigInteger("1")},
			{new BigInteger("1"), new BigInteger("2"), new BigInteger("4"), new BigInteger("8"), new BigInteger("16"), new BigInteger("32"), new BigInteger("64"), new BigInteger("128"), new BigInteger("256"), new BigInteger("512"), new BigInteger("1024"), new BigInteger("2048"), new BigInteger("4096"), new BigInteger("8192"), new BigInteger("16384"), new BigInteger("32768"), new BigInteger("65536"), new BigInteger("131072"), new BigInteger("262144"), new BigInteger("524288"), new BigInteger("1048576"), new BigInteger("2097152"), new BigInteger("4194304"), new BigInteger("8388608"), new BigInteger("16777216"), new BigInteger("33554432"), new BigInteger("67108864"), new BigInteger("134217728"), new BigInteger("268435456"), new BigInteger("536870912"), new BigInteger("1073741824"), new BigInteger("2147483648")},
			{new BigInteger("1"), new BigInteger("3"), new BigInteger("9"), new BigInteger("27"), new BigInteger("81"), new BigInteger("243"), new BigInteger("729"), new BigInteger("2187"), new BigInteger("6561"), new BigInteger("19683"), new BigInteger("59049"), new BigInteger("177147"), new BigInteger("531441"), new BigInteger("1594323"), new BigInteger("4782969"), new BigInteger("14348907"), new BigInteger("43046721"), new BigInteger("129140163"), new BigInteger("387420489"), new BigInteger("1162261467"), new BigInteger("3486784401"), new BigInteger("10460353203"), new BigInteger("31381059609"), new BigInteger("94143178827"), new BigInteger("282429536481"), new BigInteger("847288609443"), new BigInteger("2541865828329"), new BigInteger("7625597484987"), new BigInteger("22876792454961"), new BigInteger("68630377364883"), new BigInteger("205891132094649"), new BigInteger("617673396283947")},
			{new BigInteger("1"), new BigInteger("4"), new BigInteger("16"), new BigInteger("64"), new BigInteger("256"), new BigInteger("1024"), new BigInteger("4096"), new BigInteger("16384"), new BigInteger("65536"), new BigInteger("262144"), new BigInteger("1048576"), new BigInteger("4194304"), new BigInteger("16777216"), new BigInteger("67108864"), new BigInteger("268435456"), new BigInteger("1073741824"), new BigInteger("4294967296"), new BigInteger("17179869184"), new BigInteger("68719476736"), new BigInteger("274877906944"), new BigInteger("1099511627776"), new BigInteger("4398046511104"), new BigInteger("17592186044416"), new BigInteger("70368744177664"), new BigInteger("281474976710656"), new BigInteger("1125899906842624"), new BigInteger("4503599627370496"), new BigInteger("18014398509481984"), new BigInteger("72057594037927936"), new BigInteger("288230376151711744"), new BigInteger("1152921504606846976"), new BigInteger("4611686018427387904")},
			{new BigInteger("1"), new BigInteger("5"), new BigInteger("25"), new BigInteger("125"), new BigInteger("625"), new BigInteger("3125"), new BigInteger("15625"), new BigInteger("78125"), new BigInteger("390625"), new BigInteger("1953125"), new BigInteger("9765625"), new BigInteger("48828125"), new BigInteger("244140625"), new BigInteger("1220703125"), new BigInteger("6103515625"), new BigInteger("30517578125"), new BigInteger("152587890625"), new BigInteger("762939453125"), new BigInteger("3814697265625"), new BigInteger("19073486328125"), new BigInteger("95367431640625"), new BigInteger("476837158203125"), new BigInteger("2384185791015625"), new BigInteger("11920928955078125"), new BigInteger("59604644775390625"), new BigInteger("298023223876953125"), new BigInteger("1490116119384765625"), new BigInteger("7450580596923828125"), new BigInteger("37252902984619140625"), new BigInteger("186264514923095703125"), new BigInteger("931322574615478515625"), new BigInteger("4656612873077392578125")},
			{new BigInteger("1"), new BigInteger("6"), new BigInteger("36"), new BigInteger("216"), new BigInteger("1296"), new BigInteger("7776"), new BigInteger("46656"), new BigInteger("279936"), new BigInteger("1679616"), new BigInteger("10077696"), new BigInteger("60466176"), new BigInteger("362797056"), new BigInteger("2176782336"), new BigInteger("13060694016"), new BigInteger("78364164096"), new BigInteger("470184984576"), new BigInteger("2821109907456"), new BigInteger("16926659444736"), new BigInteger("101559956668416"), new BigInteger("609359740010496"), new BigInteger("3656158440062976"), new BigInteger("21936950640377856"), new BigInteger("131621703842267136"), new BigInteger("789730223053602816"), new BigInteger("4738381338321616896"), new BigInteger("28430288029929701376"), new BigInteger("170581728179578208256"), new BigInteger("1023490369077469249536"), new BigInteger("6140942214464815497216"), new BigInteger("36845653286788892983296"), new BigInteger("221073919720733357899776"), new BigInteger("1326443518324400147398656")},
			{new BigInteger("1"), new BigInteger("7"), new BigInteger("49"), new BigInteger("343"), new BigInteger("2401"), new BigInteger("16807"), new BigInteger("117649"), new BigInteger("823543"), new BigInteger("5764801"), new BigInteger("40353607"), new BigInteger("282475249"), new BigInteger("1977326743"), new BigInteger("13841287201"), new BigInteger("96889010407"), new BigInteger("678223072849"), new BigInteger("4747561509943"), new BigInteger("33232930569601"), new BigInteger("232630513987207"), new BigInteger("1628413597910449"), new BigInteger("11398895185373143"), new BigInteger("79792266297612001"), new BigInteger("558545864083284007"), new BigInteger("3909821048582988049"), new BigInteger("27368747340080916343"), new BigInteger("191581231380566414401"), new BigInteger("1341068619663964900807"), new BigInteger("9387480337647754305649"), new BigInteger("65712362363534280139543"), new BigInteger("459986536544739960976801"), new BigInteger("3219905755813179726837607"), new BigInteger("22539340290692258087863249"), new BigInteger("157775382034845806615042743")},
			{new BigInteger("1"), new BigInteger("8"), new BigInteger("64"), new BigInteger("512"), new BigInteger("4096"), new BigInteger("32768"), new BigInteger("262144"), new BigInteger("2097152"), new BigInteger("16777216"), new BigInteger("134217728"), new BigInteger("1073741824"), new BigInteger("8589934592"), new BigInteger("68719476736"), new BigInteger("549755813888"), new BigInteger("4398046511104"), new BigInteger("35184372088832"), new BigInteger("281474976710656"), new BigInteger("2251799813685248"), new BigInteger("18014398509481984"), new BigInteger("144115188075855872"), new BigInteger("1152921504606846976"), new BigInteger("9223372036854775808"), new BigInteger("73786976294838206464"), new BigInteger("590295810358705651712"), new BigInteger("4722366482869645213696"), new BigInteger("37778931862957161709568"), new BigInteger("302231454903657293676544"), new BigInteger("2417851639229258349412352"), new BigInteger("19342813113834066795298816"), new BigInteger("154742504910672534362390528"), new BigInteger("1237940039285380274899124224"), new BigInteger("9903520314283042199192993792")},
			{new BigInteger("1"), new BigInteger("9"), new BigInteger("81"), new BigInteger("729"), new BigInteger("6561"), new BigInteger("59049"), new BigInteger("531441"), new BigInteger("4782969"), new BigInteger("43046721"), new BigInteger("387420489"), new BigInteger("3486784401"), new BigInteger("31381059609"), new BigInteger("282429536481"), new BigInteger("2541865828329"), new BigInteger("22876792454961"), new BigInteger("205891132094649"), new BigInteger("1853020188851841"), new BigInteger("16677181699666569"), new BigInteger("150094635296999121"), new BigInteger("1350851717672992089"), new BigInteger("12157665459056928801"), new BigInteger("109418989131512359209"), new BigInteger("984770902183611232881"), new BigInteger("8862938119652501095929"), new BigInteger("79766443076872509863361"), new BigInteger("717897987691852588770249"), new BigInteger("6461081889226673298932241"), new BigInteger("58149737003040059690390169"), new BigInteger("523347633027360537213511521"), new BigInteger("4710128697246244834921603689"), new BigInteger("42391158275216203514294433201"), new BigInteger("381520424476945831628649898809")},
			{new BigInteger("1"), new BigInteger("10"), new BigInteger("100"), new BigInteger("1000"), new BigInteger("10000"), new BigInteger("100000"), new BigInteger("1000000"), new BigInteger("10000000"), new BigInteger("100000000"), new BigInteger("1000000000"), new BigInteger("10000000000"), new BigInteger("100000000000"), new BigInteger("1000000000000"), new BigInteger("10000000000000"), new BigInteger("100000000000000"), new BigInteger("1000000000000000"), new BigInteger("10000000000000000"), new BigInteger("100000000000000000"), new BigInteger("1000000000000000000"), new BigInteger("10000000000000000000"), new BigInteger("100000000000000000000"), new BigInteger("1000000000000000000000"), new BigInteger("10000000000000000000000"), new BigInteger("100000000000000000000000"), new BigInteger("1000000000000000000000000"), new BigInteger("10000000000000000000000000"), new BigInteger("100000000000000000000000000"), new BigInteger("1000000000000000000000000000"), new BigInteger("10000000000000000000000000000"), new BigInteger("100000000000000000000000000000"), new BigInteger("1000000000000000000000000000000"), new BigInteger("10000000000000000000000000000000")}
	};

	
	
	String intToBinary(int input, int max){
	    StringBuilder out = new StringBuilder(max);
	    out.append('1');
	    
	    for (int i = max-1; i >= 0; --i){
	        if ( input >= BASE[2][i].intValue()){
	            input%=BASE[2][i].intValue();
	            out.append('1') ;
	        } else {
	            out.append('0');
	        }
	    }

	    out.append('1');
	    return out.toString();
	}

	BigInteger stringToBase(int baseN, String input){
	    int len = input.length();
	    BigInteger out = BigInteger.ZERO;
	    for (int i = 0 ; i < len; ++i){
	        if (input.charAt(i) == '1'){
	            out = out.add(BASE[baseN][len-i-1]);
	        }
	    }
	    return out;
	}

	
	public static BigInteger sqrt(BigInteger x) {
	    BigInteger div = BigInteger.ZERO.setBit(x.bitLength()/2);
	    BigInteger div2 = div;
	    // Loop until we hit the same value twice in a row, or wind
	    // up alternating.
	    for(;;) {
	        BigInteger y = div.add(x.divide(div)).shiftRight(1);
	        if (y.equals(div) || y.equals(div2))
	            return y;
	        div2 = div;
	        div = y;
	    }
	}
	
	BigInteger getPrimeFactor(BigInteger num){
	    BigInteger factor = BigInteger.ZERO;
	    if (num.compareTo(BigInteger.valueOf(3)) < 1)
	        return factor;
	    BigInteger numSqrt = sqrt(num);
	    for (BigInteger i = BigInteger.valueOf(2); i.compareTo(numSqrt) < 1; i = i.add(BigInteger.ONE)){
	        if ( num.mod(i).equals( BigInteger.ZERO ) ){
	            return i;
	        }
	    }
	    return factor;
	}

	void doTheMagic(int N, int J){
	    int variableBits = N-2;
	    int posibilities = BASE[2][N-2].intValueExact();
	    for (int i = 0; i < posibilities && J > 0; ++i){
	        String str = intToBinary(i, variableBits);
	        boolean primeFound = false;
	        StringBuilder out = new StringBuilder(100);
	        out.append(str);
	        for (int base =2; base < 11; ++base){
	            BigInteger num = stringToBase(base, str);
	            BigInteger factor = getPrimeFactor(num);
//	            System.out.print("Base: "+base+", string: "+str);
//	            System.out.println(".\tPrime factor of "+num.toString()+" = "+factor.toString());
	            if (factor.equals(BigInteger.ZERO)){
	                primeFound = true;
	                break;
	            }
	            out.append(' ').append(factor.toString());
	        }
	        if (primeFound)
	            continue;
	        else {
	            System.out.println(out.toString());
	            --J;
	        }
	    }
	}
	
	public static void printArrays(){
		System.out.println("final BigInteger BASE[][] = {");
		for (int i = 0; i <= 10; ++i){
			BigInteger val = BigInteger.ONE;
			System.out.print("{");
			for (int m = 0; m < 32 ; ++m){
				System.out.print("new BigInteger(\""+val.toString()+ (m == 31 ? "\")":"\"), "));
				val = val.multiply(BigInteger.valueOf(i));
			}
			System.out.println("},");
		}
		
	}
	
	public static void main(String args[]){
		int T, length, outputs;
		Scanner in = new Scanner(System.in);
		T = in.nextInt();
		CoinJam cj = new CoinJam();
		for (int i = 1 ; i <= T; ++i){
			length = in.nextInt();
			outputs = in.nextInt();
			System.out.println("Case #"+i+":");
			cj.doTheMagic(length ,outputs);
		}
		in.close();
//		printArrays();
	}
}
