
#include <stdint.h>
#include <stdio.h>  //* printf *
#include <math.h>  //sqrt
#include <bits/stdc++.h>
using namespace std;
 
// int main()
// {
 
//     int n = 5, m = -5;
//     bitset<8> b(n);
//     bitset<8> b1(m);
//     cout << "Binary of 5:" << b << endl;
//     cout << "Binary of -5:" << b1 << endl;
//     return 0;
// }

bool isprime(int n);

/*Now we create 8 hash values. These are hard-coded constants 
that represent the first 32 bits of the fractional parts
of the square roots of the first 8 primes: 2, 3, 5, 7, 11, 13, 17, 19
*/
vector<uint32_t> generateConstants(int count) {
vector<float> dec;    
vector<uint32_t> h;
int n = 0;
int i = 0;
while (dec.size() < count) {
if (isprime(n)) {
    cout << "prime check >:): " << n;
    unsigned long p = n;
    p = sqrt(p) - floor(sqrt(p)); //concerned whether this will round correctly
    bitset<32> b(p);
    uint32_t hash = b; //TODO : create binary to hex function. should the binary be 32 bits or the hash? Practice bit shifting too.

    dec.push_back(hash);
    ++i; //increment index
}
++n;
    }
 return h;

}

uint32_t bintoHex(bitset<32> bin)

bool isprime(int n) { // O(n)
    if (n == 2 || n == 3) 
        return true;
    else if (n % 2 == 0)
        return false;
    for (int i = 3; i*i < n; i += 2) //check odd numbers up to sqrt(n)
    { if (n % i == 0) 
        return false;
    }
    return true;
    
    }

int main() {

vector<uint32_t> hashes = generateConstants(8);
for (int i : hashes) {
    cout << hashes[i] + " " << endl;
}

return 0;
}


//from COP3502 proj 2.

   public static short binaryStringDecode(String bin) { // method for menu option 2
        String s2 = "0b";
        if (bin.substring(0,2).equals(s2)) {
            int length = bin.length();
            bin = bin.substring(2, length); // account for 0b format
        }

        short decimalNum = 0;
        Long binary = Long.parseLong(bin);       // converts the binary String into numbers
        int k = 1;
        while (binary != 0) {

            long remainder = binary % 10;            // gets remainder of last binary digit (either 1 or 0)
            decimalNum = (short) (decimalNum + (remainder * k));    // multiply remainder by k and add to total decimal num
            k = 2 * k;                              // k is multiplied by 2 with each loop, representing 2 to the power of n as we use the bit index
            binary = binary / 10;                   // updates binary to give next digit in line

        }
        return decimalNum;
    }

    public static long hexStringDecode(String hex) { // method for menu option 1
        long decimalNumHex = 0;
        if (hex.equals("0")) { // unique case: hex = 0
           decimalNumHex = 0;
        }
        else {

            String s2 = "0x";
            if (hex.substring(0, 2).equals(s2)) {
                int length = hex.length();
                hex = hex.substring(2, length); // account for 0x format
            }

            int stringLength = hex.length();
            char digitSpot;
            short digitNum;
            long k = 1;

            for (int i = stringLength - 1; i >= 0; i--) { // for loop starts at end of hex string moving backwards & decrements i
                digitSpot = hex.charAt(i);
                digitNum = hexCharDecode(digitSpot);
                decimalNumHex = decimalNumHex + (digitNum * k);
                k = 16 * k;

                /*
                 * Each round of the FOR LOOP: uses charAt() to take each character, then decodes using the method hexCharDecode, and then adds it to the decimal number
                 * after multiplying by 16 to the power of n (given by k, which is multiplied by 16 each time)
                 *
                 *  */

            }
        }
        return decimalNumHex;
        }

    public static short hexCharDecode (char digit){ // give a number for each HEX character
            digit = Character.toUpperCase(digit); // make letters uppercase
            short digitNum;
            switch (digit) {  // switch statement evaluates HEX letter characters
                case 'A': {
                    digitNum = 10;
                    break;
                }
                case 'B': {
                    digitNum = 11;
                    break;
                }
                case 'C': {
                    digitNum = 12;
                    break;
                }
                case 'D': {
                    digitNum = 13;
                    break;
                }
                case 'E': {
                    digitNum = 14;
                    break;

                }
                case 'F': {
                    digitNum = 15;
                    break;

                }
                case '0': {
                    digitNum = 0;
                    break;
                }
                default: {
                    digitNum = (short) Character.getNumericValue(digit); // gets number from character number
                    break;
                }


            }

            return digitNum;

    }

    public static String binaryToHex(String binary) { // method for menu option 3
        short decimalNum = binaryStringDecode(binary); // invoke binaryStringDecode to convert binary to decimal
        String hexNum = ""; //initialize string hexNum;

        while (decimalNum > 0) {
            int remainder = decimalNum % 16; // keep track of remainder
          //  char rem = (char) (remainder + 55); // convert the remainder to character rem

                switch (remainder) {
                    case 10: {
                        hexNum = 'A' + hexNum;
                        break; // continue switch A-F, 10-16
                    }
                    case 11: {
                        hexNum = 'B' + hexNum;
                        break;
                    }
                    case 12: {
                        hexNum = 'C' + hexNum;
                        break;
                    }
                    case 13: {
                        hexNum = 'D' + hexNum;
                        break;
                    }
                    case 14: {
                        hexNum = 'E' + hexNum;
                        break;
                    }
                    case 15: {
                        hexNum = 'F' + hexNum;
                        break;
                    }
                    default: {
                        hexNum = remainder + hexNum; // A is 10 and ASCII is 65
                    }

                }

            decimalNum = (short) (decimalNum / 16);

            }
        

        return hexNum;

    }