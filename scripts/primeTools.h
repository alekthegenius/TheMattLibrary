#ifndef PRIMETOOLS_H
#define PRIMETOOLS_H

#include <iostream>
#include <random>
#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <sstream>
#include "randomTools.h"
using namespace std;

class primeTools {
  public:
    mpz_class primeCheck(mpz_class num);
    mpz_class primeGenerator(mpz_class bit_length, int prime_certainty);
};

mpz_class primeTools::primeCheck(mpz_class num) {
    mpz_class prime_prob = mpz_probab_prime_p(num.get_mpz_t(), 100);
    return prime_prob;
}


mpz_class primeTools::primeGenerator(mpz_class bit_length, int prime_certainty = 2) {

    randomTools random_tools;

    bool prime_flag = false;

    mpz_class rand_bits;

    do {
        rand_bits = random_tools.randomBitGenerator(bit_length);

        int prime_prob = mpz_probab_prime_p(rand_bits.get_mpz_t(), 100);

        if (prime_prob >= prime_certainty) {
            prime_flag = true;
        }
        
        
    } while (prime_flag == false);


    return rand_bits;
}





#endif