# SHA-Analyzer

Useful links for our super awesome team: <br />
SHA-256 step through & pseudocode: https://blog.boot.dev/cryptography/how-sha-2-works-step-by-step-sha-256/ <br />
git commands: https://gist.github.com/davfre/8313299 <br />
password database: https://github.com/duyet/bruteforce-database <br />


We will read in passwords from a text file, loop through the data to encrypt each password first with SHA-1 and then with SHA-256 and store it into a map of keys & encrypted passwords and a vector of decoded passwords, implementing a library to capture the time of each algorithm ie. std::chrono. <br />

*SHA-1:* <br />
This hashing algorithm encodes a string as a unique 160-bit hash value which cannot be reversed! <br />
A hash creates a signature, or digital fingerprint through a series of bitwise operations and arithmetic. The algorithm itself is rather simple compared to more computationally expensive counterparts like Bcrypt but the flipside of that is that it is weak to dictionary attacks & rainbow tables because any key will always generate the same hash. Hashing with a salt resolves this achilles' heel. <br />

*SHA-256:* <br />
From the SHA-2 family of algorithm, this hashing function creates a 256-bit digest from data. <br />

*Collisions:* <br />
If there are infinitely many passwords and only 2^160 unique hashes, there are guaranteed collisions. The SHA-1 algorithm has been broken since its inception in 1995, but it is still widely used for hashing passwords. The safe industry standard is SHA-256. <br />

*Attacks:* <br />
Hackers may wish to steal passwords by finding the string that generates the hash.
a. Dictionary Attacks
b. Rainbow Tables
