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
map<string, string> decodeAll(map<string, string> & h);
string decode(string hashed);

int main() {
    map<string, string> passwords;
    passwords["user1"] = "hello world";
    map<string, string> hashed;
    // hashed["user1"] = "AC";
    // map<string, string> dec = decodeAll(hashed);
    hashed = SHA2(passwords);
}

map<string, string> SHA2(map<string, string>& passwords) {
    // source for SHA-256 algorithm: https://blog.boot.dev/cryptography/how-sha-2-works-step-by-step-sha-256/
    // source for converting string to binary: https://stackoverflow.com/questions/10184178/fastest-way-to-convert-string-to-binary
    map<string, string> encrypted;
    string binary = "";
    
    for (auto member : passwords) {
        // username: member.first, password: member.second
        
        // step 1: pre-processing
        // 1a. convert string to binary
        for (unsigned int i = 0; i < member.second.size(); i++) {
            binary += bitset<8>(member.second.c_str()[i]).to_string();
        }
        // 1b. append 1 bit
        binary += "1";
        // 1c. padding 0's until length + 64 % 512 = 0
        //unsigned int quotient = binary.length() / 512;
        //unsigned int remainder = binary.length() % 512;
        unsigned int count0 = 512 - 64 - binary.length();
        for (unsigned int i = 0; i < count0; i++) {
            binary += "0";
        }
        string lengthBin = bitset<8>(member.second.size()).to_string();
        count0 = 64 - lengthBin.length();
        for (unsigned int i = 0; i < count0; i++) {
            binary += "0";
        }
        binary += lengthBin;
        cout << "final input: " << binary << endl;
        
        // step 2: initialize hash values

        // step 3: initialize round constants

        // step 4: chunk loop

        // step 5: create message schedule

        // step 6: compression

        // step 7: modify final values

        // step 8: concatenate final hash
        
    }
    return encrypted;
}

/*
map<string, string> decodeAll(map<string, string> & hashedPasswords) {
    map<string, string> decoded;
    for (auto member : hashedPasswords) {
        decoded[member.first] = decode(member.second);
    }
    return decoded;
}

string decode(string hashed) {
    // using brute force attack, go through all possible passwords

    string result = "";
    unsigned int maxGuessLength = 2;
    unsigned int attemap<string, string>tLength = 0;

    vector<string> hexChars = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
    
    while (result != hashed) {
        cout << "guess length: " << maxGuessLength << endl;
        cout << "current result: " << result << endl;
        cout << "attemap<string, string>t length: " << attemap<string, string>tLength << endl;
        if (attemap<string, string>tLength < maxGuessLength) {
            cout << "true" << endl;
            attemap<string, string>tLength++;
            for (unsigned int i = 0; i < hexChars.size(); i++) {
                result += hexChars.at(i);
                cout << "new result: " << result << endl;
                if (result == hashed) {
                    cout << "cracked: " << result << endl;
                    break;
                }
                if (attemap<string, string>tLength == maxGuessLength) {
                    result = result.substr(0, result.length() - 1);
                }
            }
        }
        else {
            maxGuessLength++;
            attemap<string, string>tLength = 0;
            result = "";
        }
    }

    return result;
}

*/