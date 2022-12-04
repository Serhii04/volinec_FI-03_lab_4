#pragma once

#include "galua_field_2.h"

bool is_prime(const int n){
    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        return false;
    }

    // loop to check if n is prime
    for (int i = 2; i <= n/2; ++i) {
        if (n%i == 0) {
            return false;
        }
    }

    return true;
}   


bool has_optimal_base(const int degree){
    int p = 2*degree + 1;
    
    // p must be prime
    if(!is_prime(p)){
        return false;
    }

    // find k: 2^k equal 1 (mod p)
    int mod_rez = 2;
    int k = 1;
    for(; k < p; ++k){
        if(mod_rez % p == 1){
            break;
        }

        mod_rez = (mod_rez * 2) % p;
    }

    // then we check two options for k
    // 1)
    if(k == 2*degree){
        return true;
    }

    // 2)
    if(p%4 == 3 && k == degree){
        return true;
    }

    return false;
}

table mult_matrixes(const table& l_val, const table& r_val){
    int l_height = l_val.size(), l_width = l_val[0].size();
    int r_height = r_val.size(), r_width = r_val[0].size();
    
    if(l_width != r_height){
        throw std::invalid_argument("bad matrixes with sizes: "
            + std::to_string(l_height)
            + "x"
            + std::to_string(l_width)
            + " and "
            + std::to_string(r_height)
            + "x"
            + std::to_string(r_width)
            + ".");
    }
    
    table rez = table(l_height, std::vector<bool>(r_width, 0));
    for(int i = 0; i < l_height; i++){
        for(int j = 0; j < r_width; j++){
            for(int k = 0; k < l_width; k++){
                rez[i][j] = rez[i][j] ^ (l_val[i][k] & r_val[k][j]);
            }
        }
    }

    return rez;

}

void print_table(const table& t){
    cout << "[" << endl;
    for(int i = 0; i < t.size(); i++){
        cout << "    [ ";
        for(int j = 0; j < t[0].size(); j++){
            cout << t[i][j] << " ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}


