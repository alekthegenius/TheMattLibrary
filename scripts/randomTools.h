#ifndef RANDOMTOOLS_H
#define RANDOMTOOLS_H

#include <iostream>
#include <random>
#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


class randomTools {
  public:
    mpz_class randomBitGenerator(mpz_class bit_length, vector<mpz_class> exluded_values = {});
    mpz_class randomRangeGenerator(mpz_class min_range, mpz_class max_range, vector<mpz_class> exluded_values = {});
};

mpz_class randomTools::randomBitGenerator(mpz_class bit_length, vector<mpz_class> exluded_values) {

    random_device rd;

    gmp_randclass rr(gmp_randinit_mt);
    unsigned long seed = rd();
    rr.seed(seed);

    mpz_class rand_num;

    if (exluded_values.empty()) {
        rand_num = rr.get_z_bits(bit_length);
    } else {
        do {
            rand_num = rr.get_z_bits(bit_length);
        } while (find(exluded_values.begin(), exluded_values.end(), rand_num) != exluded_values.end());
    }


    return rr.get_z_bits(bit_length);

}

mpz_class randomTools::randomRangeGenerator(mpz_class min_range, mpz_class max_range, vector<mpz_class> exluded_values) {

    random_device rd;

    gmp_randclass rr(gmp_randinit_mt);
    unsigned long seed = rd();
    rr.seed(seed);

    mpz_class rand_num;

    if (exluded_values.empty()) {
        mpz_add(rand_num.get_mpz_t(), min_range.get_mpz_t(), mpz_class(rr.get_z_range(max_range - min_range)).get_mpz_t());
    } else {
        do {
            mpz_add(rand_num.get_mpz_t(), min_range.get_mpz_t(), mpz_class(rr.get_z_range(max_range - min_range)).get_mpz_t());
        } while (find(exluded_values.begin(), exluded_values.end(), rand_num) != exluded_values.end());
    }
    

    return rand_num;
}

#endif