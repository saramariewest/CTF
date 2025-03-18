## Challenge Information
**Name:** hashcrack
**Category:** Cryptography
**Points:** 100
**Description:**
> The challenge was to acess a secret message by "cracking" hashed passwords.

## My Thought Process
1. **Understanding the challenge:**  
   - It was pretty easy and straight forward. The dificult part was to actually crack the hashes °<°
   - A sidenot: you cant actally "crack" hashes

2. **Initial Analysis:**  
   - Connecting with the server gives the first hash and a prompt to put in the identified password.
   - To "crack" the hash, I used my own script and the website `CrackSation` (https://crackstation.net/)

3. **Exploitation:**  
   - The script works as follows:
        1. Identifies the hash type based on its length (e.g., MD5, SHA-256, SHA-512).
        2. Reads a password list (rockyou.txt or another file).
        3. Calculates the hash for each password and compares it to the entered hash.
        4. If a match is found, the program outputs the original password.
        5. If no match is found, it displays an error message.


## Solution
1. **Steps I took:**  
   - I used my own script for the first two hashes
   - The third hash was much longer and my script wasn´t able to "crack" the hash, so I took the hash with me to CrackStation x)
   - With the "cracked" hash in my pocket, I went back to the server and was able to identify the last password and et voilà, I also received the flag ^^

2. **Flag:**  
   ```
   picoCTF{UseStr0nG_h@shEs_&PaSswDs!_36a1cf73}
   ```

##  Tools & Techniques Used
- hashback.c script
- CrackStation

## Lessons Learned
- I definitely need to work on my script @-@

