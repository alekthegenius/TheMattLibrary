#include <iostream>
#include <random>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <sstream>
#include "randomTools.h"
using namespace std;


struct squareVectorElement {
    mpz_class n;
    mpz_class d;
    vector<vector<mpz_class>> squareVector;
    vector<mpz_class> row_sum;
    vector<mpz_class> col_sum;

    mpz_class first_diagonal_sum;
    mpz_class second_diagonal_sum;

};

template<typename T>
bool allEqual(std::vector<T> const &v) {
    if (v.size() == 0) {
        return false;
    }
 
    return std::all_of(v.begin(), v.end(), [&] (T const &e) {
        return e == v.front();
    });
}

class parkerSquare {
    public:
        bool parkerSquareChecker(squareVectorElement parker_square);
        squareVectorElement randomSquareRangeGenerator(mpz_class n, mpz_class d, mpz_class min_range, mpz_class max_range);
};

squareVectorElement  parkerSquare::randomSquareRangeGenerator(mpz_class n, mpz_class d, mpz_class min_range, mpz_class max_range) {

    randomTools random_tools;



    vector<vector<mpz_class>> v;

    vector<mpz_class> vectorList;

    for (auto i = 0; i < n; i++) {
        vector<mpz_class> row;
        for (auto j = 0; j < n; j++) {
            mpz_class rand_num = random_tools.randomRangeGenerator(min_range, max_range, vectorList);
            vectorList.push_back(rand_num);

            mpz_class pow_rand_num;
            mpz_pow_ui(pow_rand_num.get_mpz_t(), rand_num.get_mpz_t(), d.get_ui());
            row.push_back(pow_rand_num);

        }
        v.push_back(row);
    }

    mpz_class row_length;
    mpz_sub(row_length.get_mpz_t(), n.get_mpz_t(), mpz_class(1).get_mpz_t());


    mpz_class row_height = n;

    vector<mpz_class> row_sum;
    vector<mpz_class> col_sum;

    
    mpz_class first_diagonal_sum;
    mpz_class second_diagonal_sum;

    for (int i = 0; i < v.size(); i++) { // Calculate Row Sum where i is the row index and j is the column index
        mpz_class sum = 0;
        for (int j = 0; j < v[i].size(); j++) {
            mpz_add(sum.get_mpz_t(), sum.get_mpz_t(), v[i][j].get_mpz_t());
        }
        row_sum.push_back(sum);
    }

    for (int i = 0; i < v.size(); i++) { // Calculate Column Sum where i is the column index and j is the row index
        mpz_class sum = 0;
        for (int j = 0; j < v[i].size(); j++) {
            mpz_add(sum.get_mpz_t(), sum.get_mpz_t(), v[j][i].get_mpz_t());
        }
        col_sum.push_back(sum);
    }

    cout << "Row Sum = ";
    cout << "{ ";
    for (int i = 0; i < row_sum.size(); i++) {
        cout << row_sum[i] << ", ";
    }
    cout << "}" << endl;

    cout << "Col Sum = ";
    cout << "{ ";
    for (int i = 0; i < col_sum.size(); i++) {
        cout << col_sum[i] << ", ";
    }
    cout << "}" << endl;

    for (int i = 0; i < v.size(); i++) {
        first_diagonal_sum += v[i][i];
    }
    cout << "First Diagonal Sum = " << first_diagonal_sum << endl;

    for (int i = 0; i < v.size(); i++) {
        second_diagonal_sum += v[v.size()-1-i][i];
    }

    cout << "Second Diagonal Sum = " << second_diagonal_sum << endl;


    
    cout << "Parker Square = ";

    cout << "{" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "{ ";
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << ", ";
        }
        cout << "}" << endl;
        
    }
    cout << "}" << endl;

    return {n, d, v, row_sum, col_sum, first_diagonal_sum, second_diagonal_sum};
}

bool parkerSquare::parkerSquareChecker(squareVectorElement parker_square) {


    vector<mpz_class> row_sum = parker_square.row_sum;
    vector<mpz_class> col_sum = parker_square.col_sum;

    mpz_class first_diagonal_sum = parker_square.first_diagonal_sum;
    mpz_class second_diagonal_sum = parker_square.second_diagonal_sum;

    if (allEqual(row_sum) && allEqual(col_sum) && mpz_cmp(first_diagonal_sum.get_mpz_t(), second_diagonal_sum.get_mpz_t()) == 0) {
        if (mpz_cmp(row_sum[0].get_mpz_t(), first_diagonal_sum.get_mpz_t()) == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int main() {
    parkerSquare parker_square;

    squareVectorElement solvedParkerSquare;


    cout << "Parker Square Generator (Range Mode)" << endl;
    cout << "Copyright 2025 Alek Vasek" << endl;


    string min_range_str;
    cout << "Enter Minimum Value of Parker Square (min_range): ";
    cin >> min_range_str;

    mpz_class min_range = mpz_class(min_range_str);

    string max_range_str;
    cout << "Enter Maximum Value of Parker Square (max_range): ";
    cin >> max_range_str;

    mpz_class max_range = mpz_class(max_range_str);
    
    string n_str;
    cout << "Enter Dimension of Parker Square (n): ";
    cin >> n_str;

    mpz_class n = mpz_class(n_str);

    mpz_class range;

    mpz_sub(range.get_mpz_t(), max_range.get_mpz_t(), min_range.get_mpz_t());


    mpz_class nSqrd;

    mpz_pow_ui(nSqrd.get_mpz_t(), n.get_mpz_t(), 2);


    if (mpz_cmp(range.get_mpz_t(), nSqrd.get_mpz_t()) < 0) {
        cout << "Error: Range is too small To Generate a Parker Square" << endl;
        return 1;
    }

    string d_str;
    cout << "Enter Dimension Value of Parker Square (d): ";
    cin >> d_str;

    mpz_class d = mpz_class(d_str);


    cout << "Generating Parker Square with a Min Values of " << min_range << ", Max Value of " << max_range << ", N Value of " << n << ", and Dimension Value of " << d << endl;

    
    
    do {
        solvedParkerSquare = parker_square.randomSquareRangeGenerator(n, d, min_range, max_range);
    } while (parker_square.parkerSquareChecker(solvedParkerSquare) == false);

    return 0; 

}