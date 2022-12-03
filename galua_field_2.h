#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class PolynomF2{
public:
    PolynomF2(const PolynomF2& polynom);
    PolynomF2(const int size, const bool value=false);
    PolynomF2(const std::string value);
    PolynomF2(const std::vector<bool> value);
    PolynomF2 set(const std::string value);
    PolynomF2 operator+(const PolynomF2 &r_val) const;
    PolynomF2 operator*(const PolynomF2 &r_val) const;
    PolynomF2 multiply(const PolynomF2 &r_val) const;
    PolynomF2 operator%(const PolynomF2 &mod) const;
    PolynomF2 mod(const PolynomF2 &mod) const;
    PolynomF2 operator^(const int degree) const;
    PolynomF2 square() const;
    PolynomF2 power(const int pow) const;
    PolynomF2 trace() const;
    friend std::ostream& operator<<(std::ostream &os, const PolynomF2 &polynom);
    std::string str() const;
    std::string strV() const;
    std::string strP() const;
    int degree() const;
    int size() const;
    bool at(const int i);
    PolynomF2 resize(const int size);
    PolynomF2 set(const int id, const bool value);
protected:
    std::vector<bool> value;
};

class PolynomGF2:public PolynomF2{
public:
    PolynomGF2(const PolynomGF2& polynom);
    PolynomGF2(const PolynomF2 generator, bool value=false);
    PolynomGF2(const std::string value, const PolynomF2 generator);
    PolynomGF2(const PolynomF2 polynom, const PolynomF2 generator);
    // PolynomGF2 setGenerator(const PolynomF2 generator);
    PolynomGF2 operator*(const PolynomGF2 &r_val) const;
    PolynomGF2 operator^(const int degree) const;
    PolynomGF2 power(const int degree) const;
    PolynomGF2 inverse() const;
    PolynomGF2 trace() const;
private:
    PolynomF2 generator = PolynomF2(1, false);
};

#include "PolynomF2_2.cpp"
#include "PolynomGF2_2.cpp"
