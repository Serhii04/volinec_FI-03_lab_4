#pragma once

#include "galua_field_2.h"
#include "F2_help_functions.cpp"


PolynomGF2_NB::PolynomGF2_NB(const int dim, const int value):
    PolynomF2(dim),
    mult_matrix(new table(this->get_mult_matrix())){
        this->check_base(dim);

        if(value == 1){
            for(int i = 0; i < this->value.size(); i++){
                this->value[i] = 1;
            }
        }
}

PolynomGF2_NB::PolynomGF2_NB(const PolynomF2 polynom):
    PolynomF2(polynom),
    mult_matrix(new table(this->get_mult_matrix())){
        this->check_base(polynom.size());
}

PolynomGF2_NB::PolynomGF2_NB(const PolynomGF2_NB& polynom):
    PolynomF2(polynom),
    mult_matrix(polynom.mult_matrix){
        this->check_base(polynom.size());
}

PolynomGF2_NB::PolynomGF2_NB(std::string value, const int dim):
    PolynomF2(dim),
    mult_matrix(new table(this->get_mult_matrix())){
        this->check_base(dim);
        this->set(value);
}

bool PolynomGF2_NB::check_base(const int base){
    if(!has_optimal_base(base)){
        throw std::invalid_argument("Bad base size: " + std::to_string(base) + ".");
    }

    return true;
}

PolynomGF2_NB PolynomGF2_NB::set(const std::string value){
    if(value.size() > this->size()){
        throw std::invalid_argument("Bad polynom string size: "
                                    + std::to_string(value.size())
                                    + ", while should be: "
                                    + std::to_string(this->size()) + " or less.");
    }

    for(int i = 0; i < value.size(); i++){
        if(value.at(i) == '0'){
            this->value[i] = 0;
        }else if(value.at(i) == '1'){
            this->value[i] = 1;
        }else{
            throw std::invalid_argument("Invalid string value, at id = "
                                        + std::to_string(i)
                                        + " value = "
                                        + value.at(i)
                                        + ", while only 0 and 1 values are permitted");
        }
    }

    return *this;
}

std::string PolynomGF2_NB::str() const {
    return strV();
}

std::string PolynomGF2_NB::strV() const {
    std::string rez = "";

    for(int i = 0; i < this->size(); i++){
        rez += std::to_string(value.at(i));
    }

    return rez;
}

PolynomGF2_NB PolynomGF2_NB::operator+(const PolynomGF2_NB &r_val) const{
    if(this->size() != r_val.size()){
        throw std::invalid_argument("Can't add elements with diferent sizes: "
            + std::to_string(this->size())
            + " and "
            + std::to_string(r_val.size())
            + ".");
    }
    PolynomF2 rez = PolynomF2(*this) + PolynomF2(r_val);
    return PolynomGF2_NB(rez);
}

PolynomGF2_NB PolynomGF2_NB::square() const{
    PolynomGF2_NB rez(*this);
    bool temp = rez.value.at(rez.value.size()-1);

    for(int i = value.size()-1; i > 0; i--){
        rez.value[i] = rez.value[i-1];
    }    

    rez.value[0] = temp;
    
    return rez;
}

PolynomGF2_NB PolynomGF2_NB::root() const{
    PolynomGF2_NB rez(*this);
    bool temp = rez.value.at(0);

    int last_index = value.size()-1;
    for(int i = 0; i < last_index; i++){
        rez.value[i] = rez.value[i+1];
    }    

    rez.value[value.size()-1] = temp;
    
    return rez;
}

PolynomGF2_NB PolynomGF2_NB::trace() const{
    bool rez = 0;

    for(int i = 0; i < value.size(); i++){
        rez = rez ^ value.at(i);
    }

    return PolynomGF2_NB(this->size(), rez);
}

std::vector<std::vector<bool>> PolynomGF2_NB::get_mult_matrix() const {
    std::vector<std::vector<bool>> rez = std::vector<std::vector<bool>>(this->size(), std::vector<bool>(this->size(), false));

    int p = 2*this->size() + 1;

    int temp_2_i = 1;
    int temp_2_j = 1;
    for(int i = 0; i < this->size(); i++){
        for(int j = 0; j < this->size(); j++){
            if((temp_2_i + temp_2_j)%p == 1){
                rez[i][j] = 1;
            }

            if((temp_2_i - temp_2_j)%p == 1 || (temp_2_i - temp_2_j)%p == 1 - p){
                rez[i][j] = 1;
            }

            if((-temp_2_i + temp_2_j)%p == 1 || (-temp_2_i + temp_2_j)%p == 1 - p){
                rez[i][j] = 1;
            }

            if((-temp_2_i - temp_2_j)%p == 1 || (-temp_2_i - temp_2_j)%p == 1 - p){
                rez[i][j] = 1;
            }

            temp_2_j = (temp_2_j*2)%p;
        }
        temp_2_i = (temp_2_i*2)%p;
    }

    return rez;
}

table PolynomGF2_NB::to_matrix() const{
    return table(1, this->value);
}

table PolynomGF2_NB::T() const{
    table rez = table(this->value.size(), std::vector<bool>(1, 0));

    for(int i = 0; i < this->size(); i++){
        rez[i][0] = this->value.at(i);
    }

    return rez;
}

PolynomGF2_NB PolynomGF2_NB::operator*(const PolynomGF2_NB &r_val) const{
    PolynomGF2_NB rez(*this);

    PolynomGF2_NB first(*this);
    PolynomGF2_NB second(r_val);

    for(int i = 0; i < rez.size(); i++){
        rez.value[i] = mult_matrixes(mult_matrixes(first.to_matrix(), *(this->mult_matrix)), second.T())[0][0];
        // std::cout << "matix mult:" << std::endl;
        // print_table(first.to_matrix());
        // print_table(*(this->mult_matrix));
        // std::cout << "first mult rez :" << std::endl;
        // print_table(mult_matrixes(first.to_matrix(), *(this->mult_matrix)));
        // print_table(second.T());
        // print_table(mult_matrixes(mult_matrixes(first.to_matrix(), *(this->mult_matrix)), second.T()));
        first = first.root();
        second = second.root();
    }

    return rez;
}

PolynomGF2_NB PolynomGF2_NB::operator^(const int degree) const{
    if(degree == 2){
        return this->square();
    }

    PolynomGF2_NB rez(*this);
    for(int i = 1; i < degree; i++){
        rez = rez * *this;
    }

    return rez;
}

// PolynomGF2_NB PolynomGF2_NB::inverse() const{
//     PolynomGF2_NB temp = PolynomGF2_NB(*this);
//     PolynomGF2_NB rez(this->size(), true);

//     for(int i = 1; i < this->size(); i++){
//         temp = temp.square();
//         rez = rez * temp;
//     }

//     return rez;
// }

PolynomGF2_NB PolynomGF2_NB::inverse() const{
    if(this->strP() == "0"){
        std::cerr << "zero doesn`t have invers element" << std::endl;
        throw "zero doesn`t have invers element";
    }

    int iterate_to = this->size() - 2 + 1;

    PolynomGF2_NB rez(*this);
    PolynomGF2_NB temp(*this);
    for(int i = 1; i < iterate_to; ++i){
        temp = temp.square();
        rez = rez * temp;
        // std::cout << i << ": " << rez << std::endl;
    }

    rez = rez^2;

    return rez;
}

std::ostream& operator<<(std::ostream &os, const PolynomGF2_NB &polynom ){
    os << polynom.strV();
    return os;
}

