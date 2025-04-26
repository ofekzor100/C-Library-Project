//
// Created by ofekz on 3/24/2025.
//

#ifndef LIBRARY_CPP_RSA_H
#define LIBRARY_CPP_RSA_H


class RSA {
    int n;
    int e;
    int d;
    int randomPrime(int prev,int min_value = 1000, int max_value = 10000);
    int find_encoder(int p);
    int modInverse(int e, int n);
public:
    RSA();
    int return_n();
    int return_e();
    long long RSA_D(int y);

};


#endif //LIBRARY_CPP_RSA_H
