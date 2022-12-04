#include <iostream>

#include "galua_field_2.h"

using namespace std;


int main(){ 
    PolynomGF2_NB a("11111101111", 191);
    PolynomGF2_NB b("100101001001", 191);
    PolynomGF2_NB c(191, 0);
    PolynomGF2_NB d(3, 0);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a^2 = " << a.square() << endl;
    cout << "sqrt(a^2) = " << (a.square()).root() << endl;
    cout << "trace a = " << a.trace() << endl;
    cout << "trace b = " << b.trace() << endl;
    cout << "a * b = " << a * b << endl;


    return 0;
}

