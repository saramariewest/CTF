# Hashback - Hash Cracking Tool

## Prerequisites

Before using **Hashback**, ensure you have the necessary dependencies installed:

### **1️ Install Required Packages**

For Linux (Ubuntu/Debian):

```bash
sudo apt update && sudo apt install gcc libssl-dev -y
```

For Arch Linux:

```bash
sudo pacman -S gcc openssl
```

For Windows: Install **MinGW** and OpenSSL.

### **2️ Download RockYou Wordlist**

This script requires a password list to work. The most common one is `rockyou.txt`:

```bash
wget https://example.com/rockyou.txt -O rockyou.txt
```

Alternatively, use your own password list.

---

## Compiling Hashback

Compile the program with OpenMP and OpenSSL support:

```bash
gcc -fopenmp -o hashback hashback.c -lssl -lcrypto
```

If successful, the `hashback` executable will be created.

---

## Usage

Run the script with a hash value and an optional password list:

```bash
./hashback <hash_value> [password_file]
```

### **Example Usage**

Cracking an MD5 hash using `rockyou.txt`:

```bash
./hashback 5f4dcc3b5aa765d61d8327deb882cf99 rockyou.txt
```

(Here, `5f4dcc3b5aa765d61d8327deb882cf99` is the MD5 hash of "password")

If no password file is specified, it defaults to `rockyou.txt`.

---

## Disclaimer

This tool is intended for educational purposes only. Do not use it for unauthorized access or illegal activities.

Happy cracking!

