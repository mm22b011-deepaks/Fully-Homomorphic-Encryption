# FHE - Fully Homomorphic Encryption 

This project demonstrates a simple Fully Homomorphic Encryption (FHE) example using Microsoft SEAL.  
It consists of two programs:

- **Client:** Encrypts an integer read from `number.txt` and saves the ciphertext and keys.
- **Server:** Loads the encrypted input, doubles it homomorphically, decrypts the result, and outputs the doubled value.

---

## Prerequisites

- Microsoft SEAL library installed and accessible.
- C++17 compatible compiler.
- CMake (version 3.15 or later recommended).

---

## Building

```bash
cd Fully-Homomorphic-Encryption
cd fhe
mkdir build
cd build
cmake -DSEAL_DIR=../../seal-install/lib/cmake/SEAL-4.1 ..
make -j$(nproc)
```

