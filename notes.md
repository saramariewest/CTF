# CTF Notes

This file contains useful commands, tools, and techniques I frequently use when solving CTF challenges.

---

## General Enumeration

- **Basic network scan with Nmap:**
  ```sh
  nmap -sC -sV -T4 -A <IP>
  ```
- **Check for open ports quickly:**
  ```sh
  nmap -p- --min-rate=1000 -T4 <IP>
  ```
- **Get detailed HTTP response with Curl:**
  ```sh
  curl -i -X GET <URL>
  ```

---

## Web Exploitation

- **Check website technologies:**
  ```sh
  whatweb <URL>
  ```
- **List directories with Gobuster:**
  ```sh
  gobuster dir -u <URL> -w /usr/share/wordlists/dirb/common.txt
  ```
- **Inspect and modify requests with Burp Suite**
- **Decode and encode data with CyberChef** (https://gchq.github.io/CyberChef/)

---

## Cryptography

- **Base64 Encode/Decode:**
  ```sh
  echo 'string' | base64
  echo 'c3RyaW5n' | base64 -d
  ```
- **ROT13:**
  ```sh
  echo 'uryyb' | tr 'A-Za-z' 'N-ZA-Mn-za-m'
  ```
- **Use CyberChef for complex encoding/decoding**

---

## Reverse Engineering

- **Analyze binary with Ghidra**
- **Disassemble with Radare2:**
  ```sh
  r2 -AA <binary>
  ```
- **Check for strings in a binary:**
  ```sh
  strings <binary> | less
  ```

---

## Forensics

- **Extract file metadata:**
  ```sh
  exiftool <file>
  ```
- **Inspect a PCAP file:**
  ```sh
  tshark -r <file.pcap>
  ```

---

## Miscellaneous

- **Crack hashes with Hashcat:**
  ```sh
  hashcat -m <mode> -a 0 <hashfile> <wordlist>
  ```
- **Extract hidden files from an image:**
  ```sh
  binwalk -e <image>
  ```

This list will be updated as I progress in CTF challenges!
