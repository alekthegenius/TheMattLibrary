#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "primeTools.h"

using namespace std;


int main() {
    ofstream logFile("logs.txt");

    primeTools prime_tools;
    string mode;

    mpz_class prime_certainty = 1; // Certainty of prime number; 1 = probably prime, 2 = prime
    cout << "Mode: ";
    getline (cin, mode);

    if (mode == "iterate") {

        string start_num;
        cout << "Start Number for Iterations: ";
        getline (cin, start_num);

        string end_num;
        cout << "End Number for Iterations: ";
        getline (cin, end_num);

        mpz_class iterations;

        if (mpz_class(end_num) < mpz_class(start_num)) {
            cout << "Invalid Input" << endl;
            return 0;
        }

        mpz_sub(iterations.get_mpz_t(), mpz_class(end_num).get_mpz_t(), mpz_class(start_num).get_mpz_t());

        vector<mpz_class> prime_list;


        for (mpz_class i = mpz_class(start_num); i < mpz_class(end_num); i++) {


            mpz_class is_even;

            mpz_mod(is_even.get_mpz_t(), i.get_mpz_t(), mpz_class(2).get_mpz_t());

            if (is_even == mpz_class(0)) {
                continue;
            }

            vector<mpz_class> j_list;

            mpf_class f_i = mpz_class(i) - mpz_class(start_num);              // Convert mpz_class to mpf_class
            mpf_class f_iterations = iterations;  // Convert mpz_class to mpf_class

            mpf_class percentage = (f_i / f_iterations) * 100;

            cout << "Percentage: " << percentage << endl;

            for (mpz_class j = 1; j < i; j++) {

                mpz_class current_num;
                
                
                mpz_pow_ui(current_num.get_mpz_t(), j.get_mpz_t(), 2);

                mpz_sub(current_num.get_mpz_t(), current_num.get_mpz_t(), j.get_mpz_t());

                mpz_add(current_num.get_mpz_t(), current_num.get_mpz_t(), i.get_mpz_t());


                //cout << "Current Prime Percent: " << prime_tools.primeCheck(current_num) << endl;
                if (prime_tools.primeCheck(current_num) >= prime_certainty) {


                    prime_list.push_back(current_num);
                    j_list.push_back(j);
                }
                
            }

            


            mpz_class j_list_size = j_list.size();  // Convert size_t to mpz_class

            mpf_class j_prime_percentage = (mpf_class(j_list_size) / mpf_class(i-1)) * 100;

            if (j_prime_percentage >= 50) {

                logFile << "----------------" << endl;
                
                logFile << "Caboose Number: " << i << endl;
                
                logFile << "Number of Primes: " << j_list.size() << endl;


                logFile << "Percentage of Primes: " << j_prime_percentage << endl;
            }

            j_list.clear();

            
        }


        logFile << "Number of Primes: " << prime_list.size() << endl;
    } else if (mode == "number iterator") {

        string start_num;
        cout << "Start Number: ";
        getline (cin, start_num);

        string end_num;
        cout << "Number: ";
        getline (cin, end_num);

        mpz_class iterations;

        if (mpz_class(end_num) < mpz_class(start_num)) {
            cout << "Invalid Input" << endl;
            return 0;
        }

        mpz_sub(iterations.get_mpz_t(), mpz_class(end_num).get_mpz_t(), mpz_class(start_num).get_mpz_t());

        vector<mpz_class> prime_list;

        for (mpz_class j = mpz_class(start_num); j < mpz_class(end_num); j++) {

            mpz_class current_num;
            
            
            mpz_pow_ui(current_num.get_mpz_t(), j.get_mpz_t(), 2);

            mpz_sub(current_num.get_mpz_t(), current_num.get_mpz_t(), j.get_mpz_t());

            mpz_add(current_num.get_mpz_t(), current_num.get_mpz_t(), mpz_class(end_num).get_mpz_t());


            
            if (prime_tools.primeCheck(current_num) == prime_certainty) {


                prime_list.push_back(current_num);
            }
        }

        logFile << "Caboose Number: " << end_num << endl;
        
        logFile << "Number of Primes: " << prime_list.size() << endl;

        mpf_class j_prime_percentage = (mpf_class(prime_list.size()) / mpf_class(iterations-1)) * 100;


        logFile << "Percentage of Primes: " << j_prime_percentage << endl;
    } else {
        cout << "Invalid Input" << endl;
    }

    logFile.close();
    return 0;
}

