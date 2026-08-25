#include <iostream>
#include <string>
#include <cctype>

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int getModularInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);
    if (gcd != 1) {
        return -1; 
    }
    return (x % m + m) % m;
}

// Plaintext -> Ciphertext
std::string encryptAffine(std::string text, int a, int b) {
    std::string ciphertext = "";
    
    for (char &c : text) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int x = c - base; 
            
            int encryptedChar = (a * x + b) % 26;
            
            ciphertext += (char)(encryptedChar + 'A');
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

// Ciphertext -> Plaintext
std::string decryptAffine(std::string text, int a, int b) {
    std::string plaintext = "";
    int a_inverse = getModularInverse(a, 26);
    
    if (a_inverse == -1) {
        return "ERROR: Modular inverse does not exist for key 'a'. Decryption impossible.";
    }

    for (char &c : text) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int y = c - base;\
            int decryptedChar = (a_inverse * (y - b)) % 26;
            
            if (decryptedChar < 0) {
                decryptedChar += 26;
            }
            
            plaintext += (char)(decryptedChar + 'a');
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    std::string plaintext = "hello";
    std::string ciphertext = "ZEBBW";
    int a = 7;
    int b = 2;

    std::cout << "=== AFFINE CIPHER PROGRAM ===" << std::endl;
    std::cout << "Key Pair (a, b) = (" << a << ", " << b << ")\n" << std::endl;

    std::string encryptedResult = encryptAffine(plaintext, a, b);
    std::cout << "[Encryption] Plaintext:  \"" << plaintext << "\"" << std::endl;
    std::cout << "             Ciphertext: \"" << encryptedResult << "\"\n" << std::endl;

    std::string decryptedResult = decryptAffine(ciphertext, a, b);
    std::cout << "[Decryption] Ciphertext: \"" << ciphertext << "\"" << std::endl;
    std::cout << "             Plaintext:  \"" << decryptedResult << "\"\n" << std::endl;

    return 0;
}
