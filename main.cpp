#include <iostream>

#include "galua_field_2.h"

using namespace std;

int main()
{
    int wid = 191;
    PolynomGF2_NB a("10010100100101001011101000", wid);
    PolynomGF2_NB b("000101", wid);
    PolynomGF2_NB c(wid, 1);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << endl;

    cout << "a * 0 = " << a * PolynomGF2_NB(wid, 0) << endl;
    cout << "a * 1 = " << a * PolynomGF2_NB(wid, 1) << endl;
    cout << endl;

    cout << "a^2 = " << a.square() << endl;
    cout << "trace a = " << a.trace() << endl;
    cout << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a * b = " << a * b << endl;
    cout << endl;

    cout << "(a + b) * c   = " << (a + b) * c << endl;
    cout << "a * c + b * c = " << a * c + b * c << endl;
    cout << endl;

    cout << "a^7 = " << (a ^ 7) << endl;
    cout << endl;

    c = a.inverse();
    cout << "a^-1 = " << c << endl;
    cout << "a*a^-1 = " << a * c << endl;

    return 0;
}



