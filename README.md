# MyCipher
This is a cipher dveloped by Anjinfu,for CTY Cryptology Homework.
# How it works
This cipher is straightforward to implement on a computer using a C++ program, which is open-source and available on GitHub at https://www.github.com/Anguogua/CipherAPP. Here’s a brief overview of how it works:

**1. Input and Hashing:** First, you need to enter your plaintext and key into the program. The key is hashed to generate a string that appears random. Hash functions produce a consistent output for the same input, which is used as a seed for the random number generator (RNG). This ensures that every time the same key is used, the RNG produces the same sequence of random numbers.

**2. Block Splitting and XOR Operation:** The plaintext is divided into blocks, each containing 8 characters. Each block is then encrypted using a different key derived from the RNG sequence. The XOR operation is performed on each block with its respective key. XOR, denoted as "⊕", is a binary operation where:
   - 1 ⊕ 0 = 1
   - 0 ⊕ 1 = 1
   - 1 ⊕ 1 = 0
   - 0 ⊕ 0 = 0

**3. Sorting and Conversion:** After the XOR operation, the blocks are sorted based on the values of the random keys. Finally, the program converts the binary ciphertext back into characters and outputs the result.

This process ensures that the encryption is secure and variable, with the randomness provided by the key's hash and the RNG.

# Compile
To compile this project,you need QT6 for VS2022 and Crypto++. Open CipherAPP.sln and set the path of libs and headfiles. Then, just compile it as usual.
