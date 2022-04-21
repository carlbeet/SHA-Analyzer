
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <bitset>
#include <array>
#include <math.h>
#include <locale>
#include <vector>
#include <stdint.h>
#include <stdio.h>  //* printf *
using namespace std;

/*resources! :)

Testing:
http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
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
*/
//=======================================================================================================
//source: https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf


#define SHR(str, n) (str >> n)
#define ROTR(str, n) ((str >> n) | (str << (32-n))) 
// circular right shift as noted by NIST: (x) = (x >> n) v (x << w - n).
// The following are the SHA-256 logical functions as defined by NIST
// bit rotations!
#define ch(a, b, c)  (a & b) ^ ((~a) & c)
#define maj(a, b, c)  (a & b) ^ (a & c) ^ (b & c)
#define f1(a) (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22)) //ep0
#define f2(a)  (ROTR(a, 6) ^ ROTR(a, 11) ^ ROTR(a, 25)) //ep1
#define sig1(a) (ROTR(a, 7) ^ ROTR(a, 18) ^ SHR(a, 3)) //sig0
#define sig2(a) (ROTR(a, 17) ^ ROTR(a, 19) ^ SHR(a, 10)) //sig1



int main();
string binarytoHex(string binary_string);
string floattoBinary(float num);
string decToHex(long double number);
string longtoHex(unsigned long input);

vector<unsigned long> generateConstants(int count);
map<string, string> SHA2(map<string, string>& passwords, vector<unsigned long>& k);
bool isprime(int n);


//Secure hashing algorithm - 256 functions:
// A. Preprocess string, convert it to binary and pad to 512 bits (or a multiple of 512 bits).
string preProcessor(string str);


// B. Break the 512 bit string into 32-bit words to prepare for hashing
//string padMessage512(string binary_str); <- code overlap
vector<unsigned long> getMessageSched(string binary_string);


// C. Calculate the hash value from a series of logical bitwise operations & combinations with constants
string computeHashValue(vector<unsigned long>& messSched, vector<unsigned long>& k);



int main() {

    //vector<unsigned long> RoundConstants = generateConstants(64);
    vector<unsigned long> RoundConstants = {0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
		0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
		0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
		0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
		0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
		0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
		0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
		0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
		0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2 };

    map<string, string> passwords;
    passwords["user1"] = "hello world";
    map<string, string> hashed;
    // hashed["user1"] = "AC";
    hashed = SHA2(passwords, RoundConstants);
    
}

map<string, string> SHA2(map<string, string>& passwords, vector<unsigned long>& k) {
    // source for SHA-256 algorithm: https://blog.boot.dev/cryptography/how-sha-2-works-step-by-step-sha-256/
    // source for converting string to binary: https://stackoverflow.com/questions/10184178/fastest-way-to-convert-string-to-binary
    map<string, string> encrypted;
    string binaryInput;
    unsigned int chunks;

    for (auto member : passwords) {
        // username: member.first, password: member.second

        // step 1: pre-processing
        binaryInput = preProcessor(member.second);
        // binaryInput result will always be divisible by 512
    
        // step 2: initialize hash values
        // step 3: initialize round constants
        // k passed as parameter
        // performed in step 5.

        // step 4: chunk loop
        // how many chunks there are in our binary string (1 chunch = 512 bits)
        chunks = binaryInput.length() / 512;
        // loop for every chunk
        
        for (unsigned int i = 0; i < chunks; i++) {
            string chunkStr = binaryInput.substr(i * 512, (i+1) * 512);
            cout <<  "============================================================================" << endl;
            cout << "binary: " << chunkStr << endl;
        

        // step 5: create message schedule
            vector<unsigned long> blocks = getMessageSched(chunkStr);
            // display the blocks
            for (int i = 1; i <= blocks.size(); i++) {
                cout << "BLOCK " << i << ": ";
                cout << blocks[i] << endl;
            }
            string hash = computeHashValue(blocks, k);
            cout << "hash: " << hash << endl;

        }

    }
    return encrypted;
}

//================================= SHA 256 Helper functions ======================================


string preProcessor(string str) {
    string binary = "";
    // 1a. convert string to binary
    for (unsigned int i = 0; i < str.size(); i++) {
        binary += bitset<8>(str.c_str()[i]).to_string();
    }
    const string originalBinary = binary;
    cout << "original binary: " << binary << endl;
    // 1b. append 1 bit
    binary += "1";
    // 1c. padding 0's until length + 64 % 512 = 0
    unsigned int l = str.length(); //length of message
    while (((binary.length() + 64) % 512) != 0) {
        binary += "0";
    }
    // 1d. add 64-bit value representing the length of the original string
    string lengthBin = bitset<8>(originalBinary.size()).to_string();
    unsigned int count0 = 64 - lengthBin.length();
    for (unsigned int i = 0; i < count0; i++) {
        binary += "0";
    }
    binary += lengthBin;
    // pre-processing step complete
    return binary;
}



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



// Step 5:
//input messageSchedule: 512 bit message divided into 8 bit blocks
// what we use: 1) a message schedule of sixty-four 32 bit words, 2) eight working variables of 32
// bits each, and 3) a hash value of 8 32 bit words
string computeHashValue(vector<unsigned long>& messSched, vector<unsigned long>& k) {
 // move the constants generation to parameter

//initialize constants
unsigned long h0 = 0x6a09e667;
unsigned long h1 = 0xbb67ae85;
unsigned long h2 = 0x3c6ef372;
unsigned long h3 = 0xa54ff53a;
unsigned long h4 = 0x510e527f;
unsigned long h5 = 0x9b05688c;
unsigned long h6 = 0x1f83d9ab;
unsigned long h7 = 0x5be0cd19;

//5b. Initialize array of 64 longs, manipulate with bit rotations as described by NIST;
unsigned long words[64] = {0};

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
 cout << "length of hash: " << res.length() << endl;
return res;

}



//Prepare the message schedule 
//512 bit broken into blocks of 8-bit ASCII chars
// we will use unsigned longs to compute the hash 

//input: 512 bit string
//output: vector[16] 32-bit hex digits
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
    if (p != 0 )
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

string decToHex(long double number) //double to hex string
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
// input: int number
// output: string of hex value
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
    // input: int number
    // output: string of binary digits
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
ss << hex << bits.to_ulong();
return ss.str();
}