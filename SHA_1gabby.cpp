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
using namespace std;

int main();
void readFile(string filename, map<string,string>& passwords);
map<string, string> SHA1(map<string, string>& passwords);
map<string, string> SHA2(map<string, string>& passwords);
long hexStringDecode(string hex); //hex to decimal conversion
short hexCharDecode(char digit);
string decToHex(long double number);
string decToBinary(int number);

int main() 
{
    map<string,string> passwords;
    //readFile("sampleCSV.csv", passwords);
    passwords["1"] = "abc";
    passwords["2"] = "def";
    passwords["3"] = "ghi";

    map<string, string> sha_1 = SHA1(passwords);

    cout << "New passwords:" << endl;
    for (auto iter = sha_1.begin(); iter != sha_1.end(); iter++)
    {
        cout << iter->second << endl;
    }
}

void readFile(string filename, map<string,string>& passwords) 
{
    string username; 
    string password; 
    ifstream file(filename);
    if (file.is_open()) 
    {
        getline(file, username, ','); //column title
        getline(file, password, '\n'); //column title
        while (getline(file, username, ','))
        {
            getline(file, password, '\n');
            passwords[username] = password;
        }
    }
}

map<string, string> SHA1(map<string, string>& passwords)
{
    map<string, string> encrypted;
    //iterate through passwords map
        //SHA-1 algorithm
        //1. Convert string to binary
        //2. Initialize five random strings of hex characters
        //3. Pad the message with a 1, followed by enough 0s until message is 448 bits
        //4. Then, add the length of the message (represented by 64 bits) to the end so total bits = 512
        //5. Divide each chunk into sixteen 32-bit chunks (words)
        //6. For each chunk, execute 80 iterations of the following
            //7. for iterations 16-79, perform W(i) = S^1( W(i-3) XOR W(i-8) XOR W(i-14) XOR W(i-16))
                //S^1(x) = (x << 1) left-shift
            //8. for iterations 0-79, compute TEMP = s^5 * (A) + f(i;B,C,D) + E + W(i) + K(i)
                //ABCDE = five random strings of hex characters
                //reassign variables
            //9. add ABCDE to original hex strings
        //10. final string = HH

    for (auto iter = passwords.begin(); iter != passwords.end(); ++iter)
    {
        string password = iter->second;
        string H0 = "67DE2A01";
        string H1 = "BB03E28C";
        string H2 = "011EF1DC";
        string H3 = "9293E9E2";
        string H4 = "CDEF23A9";

        unsigned long h0 = hexStringDecode(H0);
        unsigned long h1 = hexStringDecode(H1);
        unsigned long h2 = hexStringDecode(H2);
        unsigned long h3 = hexStringDecode(H3);
        unsigned long h4 = hexStringDecode(H4);

        vector<bitset<8>> binary; //vector of binary strings that should eventually total 64 (512 bits)

        int numChars = password.size(); //password.size() max = 56 characters
        int origSize = password.size();

        for (int i = 0; i < password.size(); i++) //convert every character in the password to binary and insert into vector
        {
            char character = password.at(i);
            binary.push_back(bitset<8>(character));
        }

        if (numChars < 56)
        {
            binary.push_back(bitset<8>("10000000"));
            numChars++;
            while (numChars < 56)
            {
                binary.push_back(bitset<8>("00000000"));
                numChars++;
            }
        }

        for (int i = 0; i < 7; i++) //padding before the length is added
        {
            binary.push_back(bitset<8>("00000000"));
        }

        binary.push_back(bitset<8>(password.size())); //add binary value of the password length

        vector<bitset<32>> words; //vector of "words"- 32-bit words (length should be 16)

        int numBinary = binary.size();

        for (int i = 0; i < binary.size(); i += 4)
        {
            string newWord = "";
            newWord += binary[i].to_string() += binary[i + 1].to_string() += binary[i + 2].to_string() += binary[i + 3].to_string();
            words.push_back(bitset<32>(newWord));
        }

        //append 1s and 0s to string
        //append length represented by 64 bits

        //512 bits = 64 char = 56 char + 64 bits (for length)
        //32 bits = 1 int

        bitset<32> a(h0);
        bitset<32> b(h1);
        bitset<32> c(h2);
        bitset<32> d(h3);
        bitset<32> e(h4);

        for (int i = 0; i < 80; i++)
        {
            if (i >= 16 && i <= 79)
            {
                bitset<32> x = words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16];
                bitset<32> w = (x << 1) | (x >> 31);
                words.push_back(w);
            }

            if (i >= 0 && i <= 79)
            {
                string K;
                unsigned long k;
                bitset<32> f;
                bitset<32> s = (a << 5) | (a >> 27);
                if (i >= 0 && i <= 19)
                {
                    f = (b & c) | ((~b) & d);
                    K = "5A827999";
                    k = hexStringDecode(K);
                }
                else if (i >= 20 && i <= 39)
                {
                    f = b ^ c ^ d;
                    K = "6ED9EBA1";
                    k = hexStringDecode(K);
                }
                else if (i >= 40 && i <= 59)
                {
                    f = (b & c) | (b & d) | (c & d);
                    K = "8F1BBCDC";
                    k = hexStringDecode(K);
                }
                else if (i >= 60 && i <= 79)
                {
                    f = b ^ c ^ d;
                    K = "CA62C1D6";
                    k = hexStringDecode(K);
                }

                unsigned long temp = s.to_ulong() + f.to_ulong() + e.to_ulong() + words[i].to_ulong() + k;

                e = d;
                d = c;
                c = (b << 30);
                b = a;
                a = temp;
            }
        }
        h0 = h0 + a.to_ulong();
        h1 = h1 + b.to_ulong();
        h2 = h2 + c.to_ulong();
        h3 = h3 + d.to_ulong();
        h4 = h4 + e.to_ulong();

        string hh = "";
        hh += decToHex(h0) += decToHex(h1) += decToHex(h2) += decToHex(h3) += decToHex(h4);

        encrypted[iter->first] = hh;
    }

    return encrypted;
}

map<string, string> SHA2(map<string, string>& passwords)
{
    map<string, string> encrypted;
    return encrypted;
}

long hexStringDecode(string hex) //hex to decimal conversion
{
    if (hex.length() >= 2) { //checks if the length of String hex is greater than or equal to 2
        if (hex.substr(0, 2) == "0x") { //checks if the first two characters in String hex equal "0x"
            hex = hex.substr(2, hex.length()-2); //removes the prefix "0x" from String hex
        }
    }

    long hexToDecimal = 0; 
    int hexPower = (hex.length() - 1); 
    for (int i = 0; i < hex.length(); ++i)
    {
        char digit = hex[i]; 
        short decode = hexCharDecode(digit); 
        long decodeWithPower = decode * (long)pow(16, hexPower); 
        hexToDecimal += decodeWithPower; 
        hexPower--; 
    }
    return hexToDecimal;
}

short hexCharDecode(char digit)
{
    short hexCharToDecimal = 0; 
    digit = toupper(digit); 
    if (digit == 'A') 
        hexCharToDecimal = 10; 
    else if (digit == 'B') 
        hexCharToDecimal = 11; 
    else if (digit == 'C') 
        hexCharToDecimal = 12; 
    else if (digit == 'D') 
        hexCharToDecimal = 13; 
    else if (digit == 'E')
        hexCharToDecimal = 14; 
    else if (digit == 'F') 
        hexCharToDecimal = 15;
    else 
        hexCharToDecimal = (short)(digit - '0'); 
    return hexCharToDecimal;
}

/*string decToHex(int number) //decimal to hex conversion
{
    int temp;
    string hex = "";
    vector<char> arr;

    while (number != 0)
    {
        temp = number % 16;
        if (temp < 10)
        {
            arr.push_back(48 + temp);
        }
        else
        {
            arr.push_back(55 + temp);
        }
        number /= 16;
    }

    for (int i = arr.size() - 1; i >= 0; --i)
    {
        hex += arr[i];
    }

    return hex;
}*/

string decToHex(long double number) //float/double to hex
{
    number = number * pow(2, 32);
    long long  n = (long long)(floor(number));

    // ref: https://stackoverflow.com/questions/4674956/what-are-the-first-32-bits-of-the-fractional-part-of-this-float
    //cout << "num: " << n << endl;

    int temp;
    string hex = "";
    vector<char> arr;

    if (n == 0) {
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

string decToBinary(int number) //decimal to binary conversion
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