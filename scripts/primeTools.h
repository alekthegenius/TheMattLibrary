#ifndef PRIMETOOLS_H
#define PRIMETOOLS_H

#include <iostream>
#include <random>
#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <sstream>
using namespace std;

class primeTools {
  public:
    mpz_class primeCheck(mpz_class num);
    mpz_class primeGenerator(mpz_class bit_length);
};

mpz_class primeTools::primeCheck(mpz_class num) {
    mpz_class prime_prob = mpz_probab_prime_p(num.get_mpz_t(), 100);
    return prime_prob;
}


mpz_class primeGenerator(mpz_class bit_length, int prime_certainty = 2) {

    bool prime_flag = false;

    random_device rd;
    
    gmp_randclass rr(gmp_randinit_mt);
    unsigned long seed = rd();
    rr.seed(seed);

    mpz_class rand_bits;

    do {
        rand_bits = rr.get_z_bits(bit_length);

        int prime_prob = mpz_probab_prime_p(rand_bits.get_mpz_t(), 100);

        if (prime_prob != 0) {
            prime_flag = true;
        }
        
        
    } while (prime_flag == false);


    return rand_bits;
}





#endif