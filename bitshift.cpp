
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
#include <chrono> // time durations
#include <stdint.h>
#include <stdio.h> //* printf *
using namespace std;
// DEMONSTRATION OF BIT SHIFTING

void displayShift(int n) { // n number of shifts
bitset<8> b(8);
auto copy = b;

for (int i = 0; i < n; i ++) {
copy = copy >> 1;
cout << "Right shift:" << copy << endl;
cout << "No Shift: " <<  b << endl;    
}
}

int main() {

    displayShift(5);
    return 0;
}


// #define ROTR(str, n) ((str >> n) | (str << (32-n))) 
// #define f1(a) (ROTR(a, 2) ^ ROTR(a, 13) ^ ROTR(a, 22)) //ep0

// void displayRot(int n) {
// bitset<8> b(5);
// auto copy = b;


// for (int i = 0; i < n; i ++) {
//     ROTR (copy, 1)

// }

