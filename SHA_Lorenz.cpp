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
map<string, string> SHA2(map<string, string>& passwords);
string preProcessor(string str);

int main() {
    map<string, string> passwords;
    passwords["user1"] = "hello world";
    map<string, string> hashed;
    // hashed["user1"] = "AC";
    hashed = SHA2(passwords);
}

map<string, string> SHA2(map<string, string>& passwords) {
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
        // array of hashValues represents h0-h7
        const string hashValues[8] = { "0x6a09e667", "0xbb67ae85", "0x3c6ef372", "0xa54ff53a", "0x510e527f", "0x9b05688c", "0x1f83d9ab", "0x5be0cd19" };

        // step 3: initialize round constants
        // array of round constants, fractional parts of cube roots of the first 64 primes
        const string roundConsts[64] = { "0x428a2f98", "0x71374491", "0xb5c0fbcf", "0xe9b5dba5", "0x3956c25b", "0x59f111f1", "0x923f82a4", "0xab1c5ed5",
            "0xd807aa98", "0x12835b01", "0x243185be", "0x550c7dc3", "0x72be5d74", "0x80deb1fe", "0x9bdc06a7", "0xc19bf174",
            "0xe49b69c1", "0xefbe4786", "0x0fc19dc6", "0x240ca1cc", "0x2de92c6f", "0x4a7484aa", "0x5cb0a9dc", "0x76f988da",
            "0x983e5152", "0xa831c66d", "0xb00327c8", "0xbf597fc7", "0xc6e00bf3", "0xd5a79147", "0x06ca6351", "0x14292967",
            "0x27b70a85", "0x2e1b2138", "0x4d2c6dfc", "0x53380d13", "0x650a7354", "0x766a0abb", "0x81c2c92e", "0x92722c85",
            "0xa2bfe8a1", "0xa81a664b", "0xc24b8b70", "0xc76c51a3", "0xd192e819", "0xd6990624", "0xf40e3585", "0x106aa070",
            "0x19a4c116", "0x1e376c08", "0x2748774c", "0x34b0bcb5", "0x391c0cb3", "0x4ed8aa4a", "0x5b9cca4f", "0x682e6ff3",
            "0x748f82ee", "0x78a5636f", "0x84c87814", "0x8cc70208", "0x90befffa", "0xa4506ceb", "0xbef9a3f7", "0xc67178f2"
        };


        // step 4: chunk loop
        // how many chunks there are in our binary string (1 chunch = 512 bits)
        chunks = binaryInput.length() / 512;
        // loop for every chunk
        for (unsigned int i = 0; i < chunks; i++) {
            string chunkStr = binaryInput.substr(i * 512, 64);
            cout << chunkStr << endl;
            // step 5: create message schedule

            // step 6: compression

            // step 7: modify final values

        }

        // step 8: concatenate final hash

        // delete arrays
        delete[] hashValues;
        delete[] roundConsts;

    }
    return encrypted;
}

string preProcessor(string str) {
    string binary = "";
    // 1a. convert string to binary
    for (unsigned int i = 0; i < str.size(); i++) {
        binary += bitset<8>(str.c_str()[i]).to_string();
    }
    const string originalBinary = binary;
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