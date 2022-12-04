#pragma once

#include "galua_field_2.h"

PolynomF2::PolynomF2(const PolynomF2& polynom){
    this->value = std::vector<bool>(polynom.value);
}

PolynomF2::PolynomF2(const int size, const bool value){
    if(size < 1){
        std::cerr << "ERROR: size must be greather 0, while " 
            << std::to_string(size) 
            << " was given." 
            << std::endl;
    }

    this->value = std::vector<bool>(size, false);
    this->value[0] = value;
}

PolynomF2::PolynomF2(const std::string value){
    this->value = std::vector<bool>(value.size(), false);

    set(value);
}

PolynomF2::PolynomF2(const std::vector<bool> value){
    if(value.size() == 0){
        std::cerr << "size of value array must be greather than 0 while get 0" << std::endl;
        throw "size of value array must be greather than 0 while get 0";
    }

    this->value = value;
}

PolynomF2 PolynomF2::set(const std::string value){
    if(value.size() > this->size()){
        std::cerr << "ERROR: size of given value: " << std::to_string(value.size()) 
            << " is greather than field size: " << std::to_string(this->size()) << std::endl;

        throw "ERROR: [[[[]]]]";
    }

    int i = value.size()-1;  // new value iterator id
    int j = 0;  // curent value iterator id
    
    while(i > -1){
        if(value.at(i) == '0'){
            this->value[j] = 0;
        }else{
            this->value[j] = 1;
        }
        j += 1;
        i -= 1;
    }

    return *this;
}

PolynomF2 PolynomF2::operator+(const PolynomF2 &r_val) const {
    if(this->size() != r_val.size()){
        std::cerr << "ERROR: cand apend elements, they are from diferent fields" << std::endl;
    }
    PolynomF2 rez(this->size());

    for(int i = 0; i < this->size(); ++i){
        rez.value[i] = this->value.at(i) ^ r_val.value.at(i);
    }

    return rez;
}

PolynomF2 PolynomF2::operator*(const PolynomF2 &r_val) const {
    PolynomF2 rez = this->multiply(r_val);

    return rez.resize(this->size());
}

PolynomF2 PolynomF2::multiply(const PolynomF2 &r_val) const{
    int rez_degree = r_val.degree() + this->degree();
    PolynomF2 rez(rez_degree + 1);
    
    // k is index of result polinom
    for(int k = 0; k < rez.size(); ++k){
        // the next is formula: rez_k = sum_{i=0}^k this_i * r_val_{k-i}
        // where + is ^, and * is &
        for(int i = 0; i <= k; ++i){
            if(i < this->size() && (k-i) < r_val.size()){
                rez.value[k] = rez.value.at(k) ^ (this->value.at(i) & r_val.value.at(k-i));
            }
        }
    }

    return rez;
}

PolynomF2 PolynomF2::operator%(const PolynomF2 &mod) const{
    PolynomF2 rez = this->mod(mod);

    return rez.resize(mod.degree());
}

PolynomF2 PolynomF2::mod(const PolynomF2 &mod) const {
    PolynomF2 rez(*this);
    PolynomF2 m(mod);
    int diff = this->degree() - m.degree();

    // diference (this.degree() - mod.degree()) must be -1 or less
    while(diff > -1){
        int i = mod.degree();
        int j = rez.degree();

        while(i > -1){
            rez.value[j] = rez.value.at(j) ^ mod.value.at(i);
            i -= 1;
            j -= 1;
        }

        diff = rez.degree() - mod.degree();
    }

    return rez;
}

PolynomF2 PolynomF2::operator^(const int degree) const{
    return this->power(degree).resize(this->size());
}

PolynomF2 PolynomF2::square() const {
    int degree = this->degree();
    PolynomF2 rez(degree*2 + 1);
    
    for(int i = 0; i <= degree; ++i){
        rez.set(2*i, this->value.at(i));
    }

    return rez;
}

PolynomF2 PolynomF2::power(const int pow) const{
    if(pow == 2){
        return this->square();
    }

    // std::cout << " [[[BAD POVER]]] ";  // for debuging
    PolynomF2 rez(*this);
    for(int i = 1; i < pow; ++i){
        rez = rez.multiply(*this);
    }

    return rez;
}

PolynomF2 PolynomF2::trace() const{
    return *this;
}

std::ostream& operator<<(std::ostream &os, const PolynomF2 &polynom ){
    os << polynom.str();
    return os;
}

std::string PolynomF2::str() const {
    return strV();
}

std::string PolynomF2::strV() const {  // represent polinom like vector: a_n a_(n-1) ... a_1 a_0
    std::string rez = "";

    for(int i = value.size()-1; i > -1; --i){
        rez += std::to_string(value.at(i));
    }

    return rez;
    // return "<size=" + std::to_string(this->size()) + ": value=" + rez + ">";
}

std::string PolynomF2::strP() const {  // represent polinom like normal polinom: x^2 + x + 1
    std::string rez = "";

    for(int i = value.size()-1; i > 1; --i){  // add to res all povers but 1 and 0. for beautifull view
        if(value.at(i) != 0){
            if(rez != ""){
                rez += " + ";
            }
            
            rez += "x^" + std::to_string(i);
        }
    }

    if(value.size() > 2 && value.at(1) == true){  // add x to rez if should
        if(rez != ""){
            rez += " + x";
        }else{
            rez = "x";
        }
    }
    
    if(value.at(0) == true){  // add 1 to rez if should
        if(rez != ""){
            rez += " + 1";
        }else{
            rez = "1";
        }
    }

    if(rez == ""){  // check if value is 0. it mustn`t be empty string
        return "0";
    }

    return rez;
}

int PolynomF2::size() const{
    return this->value.size();
}

bool PolynomF2::at(const int i){
    return this->value.at(i);
}

PolynomF2 PolynomF2::resize(const int size){
    if(size < this->size()){  // do if new size is less than old
        this->value.resize(size);
        return *this;
    }

    while(size > this->size()){  // do if there is a need to increase the size
        //  THINK ABOUT IF THERE IS CREATED FUNCTION IN STD FOR IT
        this->value.push_back(false);
    }

    return *this;
}

PolynomF2 PolynomF2::set(const int id, const bool value){
    if(id < 0){
        throw "ERROR: id must be greather 0 while get: " + std::to_string(id);
    }

    if(id > this->size()-1){
        throw "ERROR: out of range, get id: " + std::to_string(id) 
        + " while size is: " + std::to_string(this->size());
    }

    this->value[id] = value;

    return *this;
}
































int PolynomF2::degree() const {
    if(this->size() == 0){
        std::cerr << "zero size" << std::endl;
    }
    for(int i = this->size()-1; i > -1; --i){
        if(this->value.at(i) == true){
            return i;
        }
    }

    return 0;
}


