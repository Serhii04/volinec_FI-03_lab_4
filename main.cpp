#include <iostream>

#include "galua_field_2.h"

using namespace std;

int main()
{
    int wid = 191;
    PolynomGF2_NB a("011", wid);
    PolynomGF2_NB b("101", wid);
    PolynomGF2_NB c(wid, 0);
    PolynomGF2_NB d(3, 0);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a^2 = " << a.square() << endl;
    cout << "sqrt(a^2) = " << (a.square()).root() << endl;
    cout << "trace a = " << a.trace() << endl;
    // cout << "trace b = " << b.trace() << endl;
    cout << "a * b = " << a * b << endl;
    // cout << "a * c = " << a * c << endl;
    // cout << "a * 1 = " << a * PolynomGF2_NB(wid, 1) << endl;
    // cout << "x * x = " << PolynomGF2_NB("1", wid) * PolynomGF2_NB("1", wid) << endl;
    // cout << "x^2 * x^2 = " << PolynomGF2_NB("01", wid) * PolynomGF2_NB("01", wid) << endl;
    // cout << "a^4 = " << (a ^ 4) << endl;
    // // c = a^2;
    // cout << "a^2 = " << (a.square()) << endl;
    // cout << "a*a = " << (a*a) << endl;

    cout << "a       = " << a << std::endl;
    cout << "(a^2)^2 = " << (a.square().square()) << endl;
    cout << "a^4     = " << (a^4) << endl;
    cout << "a*a*a*a = " << (a*a*a*a) << endl;

    // print_table(a.get_mult_matrix());
    c = a.inverse();
    cout << "a^-1 = " << c << endl;
    cout << "a*a^-1 = " << a * c << endl;

    return 0;
}
