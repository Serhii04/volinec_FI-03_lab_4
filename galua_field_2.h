#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

typedef std::vector<std::vector<bool>> table;

bool has_optimal_base(const int degree);

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

class PolynomGF2_NB:public PolynomF2{
public:
    PolynomGF2_NB(const int dim, const int value=0);
    PolynomGF2_NB(const PolynomF2 polynom);
    PolynomGF2_NB(const PolynomGF2_NB& polynom);
    PolynomGF2_NB(std::string value, const int dim);
    PolynomGF2_NB set(const std::string value);
    bool check_base(const int base);
    std::string str() const;
    std::string strV() const;
    PolynomGF2_NB operator+(const PolynomGF2_NB &r_val) const;
    PolynomGF2_NB square() const;
    PolynomGF2_NB root() const;
    PolynomGF2_NB trace() const;
    PolynomGF2_NB operator*(const PolynomGF2_NB &r_val) const;
    std::vector<std::vector<bool>> get_mult_matrix() const;
    std::vector<std::vector<bool>> to_matrix() const;
    std::vector<std::vector<bool>> T() const;
    // PolynomGF2_NB operator^(const int degree) const;
    // PolynomGF2_NB T() const;
    friend std::ostream& operator<<(std::ostream &os, const PolynomGF2_NB &polynom);
};

#include "F2_help_functions.cpp"
#include "PolynomF2_2.cpp"
#include "PolynomGF2_2.cpp"
#include "PolynomGF2_NB.cpp"
