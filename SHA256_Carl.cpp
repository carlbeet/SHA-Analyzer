
#include <stdint.h>
#include <stdio.h>  //* printf *
#include <math.h>  //sqrt

#include <bitset>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
//resources! :)
/*

Testing:
http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
Implementations:
http://www.zedwood.com/article/cpp-sha256-function
NIST:
https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf

Terminology:
groups of 32 bits are called "words"

NIST: "1. A hex digit is an element of the set {0, 1,…, 9, a,…, f}. A hex digit is the
representation of a 4-bit string. For example, the hex digit “7” represents the 4-bit
string “0111”, and the hex digit “a” represents the 4-bit string “1010”.

2.	 A word is a w-bit string that may be represented as a sequence of hex digits. To
convert a word to hex digits, each 4-bit string is converted to its hex digit equivalent,
as described in (1) above. For example, the 32-bit string "

string createHash(vector<string>& block) {
return "";
}
// hardcoded hash things
// 	k = {0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
// 		0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
// 		0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
// 		0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
// 		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
// 		0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
// 		0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
// 		0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
// 		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
// 		0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
// 		0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2 }

*/
//These words represent the first 32
//bits of the fractional parts of the cube roots of the first sixty-
//four prime numbers.

//=======================================================================================================
//source: https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf


#define SHR(str, n) (str >> n)
#define ROTR(str, n) ((str >> n) | (str << (32-n))) 
// circular right shift as noted by NIST: (x) = (x >> n) v (x << w - n).
// The following are the SHA-256 logical functions as defined by NIST
// bit rotations!
#define ch(a, b, c) = (a & b) ^ ((~a) & c)
#define maj(a, b, c) = (a & b) ^ (a & c) ^ (b & c)
#define f1(a) = (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22)) //ep0
#define f2(a) = (ROTR(a, 6) ^ ROTR(a, 11) ^ ROTR(a, 25)) //ep1
#define sig1(a) = (ROTR(a, 7) ^ ROTR(a, 18) ^ SHR(a, 3)) //sig0
#define sig2(a) = (ROTR(a, 17) ^ ROTR(a, 19) ^ SHR(a, 10)) //sig1

bool isprime(int n) { // O(n)
    if (n == 2 || n == 3) 
        return true;
    else if (n % 2 == 0)
        return false;
    for (int i = 3; i*i <= n; i += 2) //check odd numbers up to sqrt(n)
    { if (n % i == 0) 
        return false;
    }

    return true;
}

string computeHashValue(vector<unsigned long> messSched);
vector<unsigned long> generateConstants(int count);
vector<unsigned long> getMessageSched(string binary_string);
string padMessage512(string binary_str)

string binarytoHex(string binary_string);
string floattoBinary(float num);
string decToHex(long double number)
string longtoHex(unsigned long input);


// Step 5:
//input messageSchedule: 512 bit message divided into 8 bit blocks
string computeHashValue(vector<unsigned long>& messSched, vector<unsigned long> k) {
// what we use: 1) a message schedule of sixty-four 32 bit words, 2) eight working variables of 32
// bits each, and 3) a hash value of 8 32 bit words

 // move the constants generation to parameter


//initialize constants
unsigned long h0 = 0x6a09e667;
unsigned long h1 = 0xbb67ae85;
unsigned long h2 = 0x3c6ef372;
unsigned long h3 = 0xa54ff53a;
unsigned long h4 = 0x510e527f;
unsigned long h5 = 0x9b05688c;
unsigned long h6= 0x1f83d9ab;
unsigned long h7 = 0x5be0cd19;

//5b. Initialize array of 64 longs to 0
<unsigned long> words[64] = {0};

	for(int i = 0; i < 16; i++)
	{
		words[i] = messSched[i] & 0xFFFFFFFF; //& with OxFFFFFFFF makes sure any bits over the 32 are zeroed out
    }
	for(int i = 16; i < 64; i++)
	{//NIST
	    words[i] = sig2(words[i-2]) + words[i-7] + sig1(words[i-15]) + words[i-16];

		//32 bits
		words[i] = words[i] & 0xFFFFFFFF;
	}

    //Step 6: Compression function ==================================================================

    unsigned long temp1;
	unsigned long temp2;
	unsigned long a = h0;
	unsigned long b = h1;
	unsigned long c = h2;
	unsigned long d = h3;
	unsigned long e = h4;
	unsigned long f = h5;
	unsigned long g = h6;
	unsigned long h = h7;

for (int i = 0; i < 64; i ++) {     
        temp1 = h + f2(e) + ch(e,f,g) + k[i] + words[i];
        temp2 = f1(a) + maj(a,b,c);
        h = g;
        g = f;
        f = e;
        e = (d + temp1) & 0xFFFFFFFF;
        d = c;
        c = b;
        b = a;
        a = (temp1 + temp2) & 0xFFFFFFFF;

    }

//afterwards: 
h0 = h0 + a;
h1 = h1 + b;
h2 = h2 + c;
h3 = h3 + d;
h4 = h4 + e; 
h5 = h5 + f;
h6 = h6 + g;
h7 = h7 + h;

string res = longtoHex(h0) + longtoHex(h1) + longtoHex(h2) + longtoHex(h3) + longtoHex(h4) + longtoHex(h5)
 + longtoHex(h6) + longtoHex(h7);
return res;
}



//512 bit broken into blocks of 8-bit ASCII chars
// we will use unsigned longs to compute the hash 
//Prepare the message schedule

//input: 512 bit string
// output: vector[16] 32-bit hex digits
vector<unsigned long> getMessageSched(string binary_string) { //pass in 512 bit binary string
vector<unsigned long> messageSched; 
unsigned long w;
// create 32-bit blocks
 for (int i = 0; i < 16; i++)
        {
            string word = binary_string.substr(32* (i), 32*(i+1));
            bitset<32> set(word);  
            messageSched.push_back(set.to_ulong()) ;
            cout << "word: " << hex << set.to_ulong() << endl;
            
        }
return messageSched;
}

vector<unsigned long> generateConstants(int count) {

// SHA-256 uses a sequence of sixty-four constant 32-bit words represented as hex values. 
// words represent the first 32 bits of the fractional parts of the cube roots
// of the first 64 prime numbers. 
// Rather than hardcode the constants, we generated them through these functions.

vector<unsigned long> h;
int n = 0;
int i = 0;
while (i < count) {
if (isprime(n)) {
    cout << "prime number: " << n << endl;
    long double p = (long double) n;
    p = cbrt(p) - floor(cbrt(p)); //"fractional part"
    cout << "dec part: " << p << endl;
    //string binary = floattoBinary(p); 
    //string hex = binarytoHex(binary); //TODO : create binary to hex function. should the binary be 32 bits or the hash? Practice bit shifting too.
    if (p !=0 )
    {
        string hex = decToHex(p);
        bitset<32> set(hex);
        // send back unsigned long hexdigits representing the binary of hex string
        h.push_back(set.to_ulong());
        ++i; //increment index
    }
}
++n;
    }
 return h;

}

string decToHex(long double number) //float/double to hex
{   
    number = number * pow(2, 32);
    long long  n = (long long) (floor(number));

    // ref: https://stackoverflow.com/questions/4674956/what-are-the-first-32-bits-of-the-fractional-part-of-this-float
    cout << "num: " << n << endl;

    int temp;
    string hex = "";
    vector<char> arr;

    if (n == 0){
    hex = "000000";
    }

    while (n != 0)
    {
        temp = n % 16;
        if (temp < 10)
        {
            arr.push_back(48 + temp);
        }
        else
        {
            arr.push_back(55 + temp);
        }
        n /= 16;
    }

    for (int i = arr.size() - 1; i >= 0; --i)
    {
        hex += arr[i];
    }

    return hex;
}

string decToHex(int number) //overloaded method, this one is int to hex
{   
    int n = number; //any typecasting should go here.
    int temp;
    string hex = "";
    vector<char> arr;

    if (n == 0){
    hex = "000000";
    }

    while (n != 0)
    {
        temp = n % 16;
        if (temp < 10)
        {
            arr.push_back(48 + temp);
        }
        else
        {
            arr.push_back(55 + temp);
        }
        n /= 16;
    }

    for (int i = arr.size() - 1; i >= 0; --i)
    {
        hex += arr[i];
    }

    return hex;
}

string decToBinary(int number)
{
    string temp = "";
    string binary = "";
    
    while (number > 0)
    {
        temp += to_string(number % 2);
        number /= 2;
    }

    for (int i = temp.size() - 1; i >= 0; i--)
    {
        binary += temp[i];
    }

    return binary;
}



string binarytoHex(string binary_string) { //pass around binary as strings, convert to and from bitset.
// input: binary string
// output: string of hex value 
bitset<32> bits(binary_string);
stringstream ss;
ss << hex << bits.to_ulong() << endl;
return ss.str();

}
string longtoHex(unsigned long input) { //pass around binary as strings, convert to and from bitset.
// input: binary string
// output: string of hex value 
bitset<32> bits(input);
stringstream ss;
ss << hex << bits.to_ulong() << endl;
return ss.str();


}


void displayShift(int n) { // n number of shifts
bitset<8> b(5);
auto copy = b;

for (int i = 0; i < n; i ++) {
copy = copy >> 1;
cout << "Right shift:" << copy << endl;
cout << "Right Shift: " <<  b << endl;    
}
}

//Preprocessing
//pad message to 512 bits
string padMessage512(string binary_str) { //512 - 64 = 448

int l =  binary_str.length(); //length of message
binary_str += "1"; //append 1 bit

string extrabits = decToBinary(l); 
cout << "message length in binary" << extrabits << " ";

int k = (448%512) - l - 1; // num zeroes to pad
int step =  k / 8;
int stepones = k % 8;

for (int i = 0; i < step; i ++) {
    binary_str += "00000000";
}
for (int i = 0; i < stepones + 64 - (int) extrabits.length(); i ++) {
    binary_str += "0";
}

binary_str += extrabits;

cout << "check 512: " << binary_str.length();
return binary_str;
}
//I haven't tested this extensively but length checks out







int main() {

string bin = "011010000110010101";
string b2 = padMessage512(bin);

vector<unsigned long> k = generateConstants(64);

// vector<string> k = generateConstants(64);
// for (auto i : k) {
//     cout << i << endl;
// }


// displayShift(20);
   return 0;
}


/* Our Operations:
 1. &, |, and ^ (XOR)
 2. Addition modulo 2^32. z = (x + y) mod(2^32)



//display right shift: i << 1
//display right rotate:

// using namespace std;
// int main(){
//     string binary_str("11001111");
//     bitset<8> set(binary_str);  
//     cout << hex << set.to_ulong() << endl;
// }


/* Function : convert_to_binary
Takes the string and convers all characters to the binary
*/