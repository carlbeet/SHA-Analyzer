# SHA-Analyzer

We will read in passwords from a text file, loop through the data to encrypt each password first with SHA-1 and then with SHA-256 and store it into a map of keys & encrypted passwords and a vector of decoded passwords, implementing a library to capture the time of each algorithm ie. std::chrono.

*SHA-1:*
This hashing algorithm encodes a string as a unique 160-bit hash value which cannot be reversed!
A hash creates a signature, or digital fingerprint through a series of bitwise operations and arithmetic. The algorithm itself is rather simple compared to more computationally expensive counterparts like Bcrypt but the flipside of that is that it is weak to dictionary attacks & rainbow tables because any key will always generate the same hash. Hashing with a salt resolves this achilles' heel.

*SHA-2:*

*Collisions:*
If there are infinitely many passwords and only 2^160 unique hashes, there are guaranteed collisions. The SHA-1 algorithm has been broken since its inception in 1995, but it is still widely used for hashing passwords. The safe industry standard is SHA-256.

*Attacks:*
Hackers may wish to steal passwords by finding the string that generates the hash.
a. Dictionary Attacks
b. Rainbow Tables
