//
// Created by ofekz on 3/24/2025.
//

#include "RSA.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int RSA::randomPrime(int prev,int min_value, int max_value) {
    srand(time(0)); // Seed for random number generation
    while (true) {
        int num = rand() % (max_value - min_value + 1) + min_value; // Generate random number
        if (isPrime(num) && num!=prev) {  // Check if it's prime
            return num;
        }
    }
}


// Function to find a random e such that gcd(e, p) = 1
int RSA::find_encoder(int p) {
    srand(time(0)); // Seed for random number generation
    int e;
    while (true) {
        e = rand() % (p - 2) + 2; // Generate random e between 2 and p-1
        if (gcd(e, p) == 1) {
            return e; // e is coprime with p
        }
    }
}

RSA::RSA() {
    int p=randomPrime(1);
    int q= randomPrime(p);
    int e= find_encoder((p-1)*(q-1));
    this->e=e;
    this->n= p*q;
    this->d= modInverse(e,(p-1)*(q-1));
}



// Function to compute the modular inverse (e^-1 mod n) using the Extended Euclidean Algorithm
int RSA:: modInverse(int e, int n) {
    int t = 0;
    int newT = 1;
    int r = n;
    int newR = e;

    // Extended Euclidean Algorithm
    while (newR != 0) {
        int quotient = r / newR;

        // Update t and r
        int tempT = t;
        t = newT;
        newT = tempT - quotient * newT;

        int tempR = r;
        r = newR;
        newR = tempR - quotient * newR;
    }

    // If the GCD is not 1, then the modular inverse doesn't exist
    if (r > 1) {
        std::cout << "Inverse does not exist\n";
        return -1;  // Return -1 if no modular inverse exists
    }

    // Make sure the result is positive
    if (t < 0) {
        t = t + n;
    }

    return t;
}

int RSA::return_n() {
    return this->n;
}

int RSA::return_e() {
    return this->e;
}

// Function to compute y^d mod n using modular exponentiation
long long modExponentiation(int y, int d, int n) {
    long long answer = 1;
    for(long long i=0;i<d;i++){
        answer = (answer*y)%n;
    }
    return answer%n;
}

long long RSA::RSA_D(int y) {
    return modExponentiation(y,this->d,this->n);
}





