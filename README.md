# SHA-Analyzer


DATA ENCRYPTION
SHA Analyzer

Team: Final Project 98
Members: Gabrielle Richards, Lorenz Carvajal, Carl Noll

Useful links for our super cool team: <br />
SHA-256 step through & pseudocode: https://blog.boot.dev/cryptography/how-sha-2-works-step-by-step-sha-256/ <br />
git commands: https://gist.github.com/davfre/8313299 <br />
password database: https://github.com/duyet/bruteforce-database <br />


We will read in passwords from a text file, loop through the data to encrypt each password first with SHA-1 and then with SHA-256 and store it into a map of keys & encrypted passwords and a vector of decoded passwords, implementing a library to capture the time of each algorithm ie. std::chrono. <br />

*SHA-1:* <br />
This hashing algorithm encodes a string as a unique 160-bit hash value which cannot be reversed! <br />
A hash creates a signature, or digital fingerprint through a series of bitwise operations and arithmetic. The algorithm itself is rather simple compared to more computationally expensive counterparts like Bcrypt but the flipside of that is that it is weak to dictionary attacks & rainbow tables because any key will always generate the same hash. Hashing with a salt resolves this achilles' heel. <br />

*SHA-256:* <br />
From the SHA-2 family of algorithm, this hashing function creates a 256-bit digest from an input. While SHA-1 is broken, SHA-256 is widely used because there is no known collision for it. We expect SHA-256 to take much longer for hash generation because it is computationally more "massive" than SHA-1. <br />

*Collisions:* <br />
If there are infinitely many passwords and only 2^160 unique hashes, there are guaranteed collisions. The SHA-1 algorithm has been broken since its inception in 1995, but it is still widely used for hashing passwords. The safe industry standard is SHA-256, which has no known collisions. However, it is still essential to use a unique salt to safely implement this algorithm. <br />

*Attacks:* <br />
Hackers may wish to steal passwords by finding the string that generates the hash.
a. Dictionary Attacks
  This is the brute force method of password hacking, wherein the attacker tries every possible combination. It takes a lot of time and resources to run this kind of attack, but it will be successful if entries are not salted.
b. Rainbow Tables
  Time space tradeoff using reduction functions. Makes hash lookup much quicker through a chaining mechanism.
