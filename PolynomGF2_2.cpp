#include "galua_field_2.h"

PolynomGF2::PolynomGF2(const PolynomGF2& polynom):
    PolynomF2(polynom),
    generator(polynom.generator){
}

PolynomGF2::PolynomGF2(PolynomF2 generator, bool value):
    PolynomF2(generator.size()-1, value),
    generator(generator){
}

PolynomGF2::PolynomGF2(std::string value, PolynomF2 generator):
    PolynomF2((PolynomF2(value) % generator)),  // might be error
    generator(generator){
        // std::cout << "created: " << *this << std::endl;  // for debug
}

PolynomGF2::PolynomGF2(PolynomF2 polynom, PolynomF2 generator):
    PolynomF2(polynom % generator), generator(generator){
        // next isnt nesesary because operation % in PolynomF2 do it for you 
        // resize(generator.size()-1);
}

// setGenerator is skiped now becouse of it`s unnesesity

PolynomGF2 PolynomGF2::operator*(const PolynomGF2 &r_val) const{
    PolynomF2 rez = multiply(r_val) % this->generator;
    // std::cout << "multiple time-var rez = " << rez << std::endl;
    PolynomGF2 rez_gf2 = PolynomGF2(rez, this->generator);
    // rez_gf2.resize(this->generator.size()-1);

    return rez_gf2;
}

PolynomGF2 PolynomGF2::operator^(const int degree) const{
    PolynomF2 rez_f2 = this->power(degree);
    
    return PolynomGF2(rez_f2, this->generator);
}

PolynomGF2 PolynomGF2::power(const int degree) const{
    if(degree == 2){
        return PolynomGF2(this->square(), this->generator);
    }

    // std::cout << " [[[BAD POVER]]] ";  // for debuging
    PolynomGF2 rez(*this);
    for(int i = 1; i < degree; ++i){
        // std::cout << i << std::endl;
        rez = rez * (*this);
        // std::cout << "multiplicational rez = " << rez << std::endl;
    }

    return rez;
}

PolynomGF2 PolynomGF2::inverse() const{
    if(this->strP() == "0"){
        std::cerr << "zero doesn`t have invers element" << std::endl;
        throw "zero doesn`t have invers element";
    }

    // iterate to m - 2 and + 1 because we will iterate: for i < iterate_to
    int iterate_to = this->generator.degree() - 2 + 1;

    PolynomGF2 rez(*this);
    PolynomGF2 temp(*this);
    for(int i = 1; i < iterate_to; ++i){
        temp = temp^2;
        rez = rez * temp;
    }

    rez = rez^2;

    return rez;
}

PolynomGF2 PolynomGF2::trace() const{
    // iterate to m - 2 and + 1 because we will iterate: for i < iterate_to
    int iterate_to = this->generator.degree() - 1 + 1;

    PolynomGF2 rez(*this);
    PolynomGF2 temp(*this);
    // start from i = 1 becouse we already have this^(2^0) = this^1
    for(int i = 1; i < iterate_to; ++i){
        temp = temp^2;
        rez = PolynomGF2(rez + temp, this->generator);
    }

    return rez;
}


