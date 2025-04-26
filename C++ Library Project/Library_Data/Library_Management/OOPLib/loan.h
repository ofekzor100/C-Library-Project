//
// Created by ofekz on 3/11/2025.
//

#ifndef MAIN_CPP_LOAN_H
#define MAIN_CPP_LOAN_H
#include <string>
#include <iostream>
using std::string;

class loan {
    string ISBN;
    int start_day;
    int start_month;
    int start_year;
    int end_day;
    int end_month;
    int end_year;
public:
    loan(string ISBN,int start_day,int start_month,int start_year,int end_day,int end_month,int end_year);
    ~loan()=default;
    int get_end_year() const;
    int get_end_month() const;
    int get_end_day() const;
    string get_ISBN() const;
    int get_start_year() const;
    int get_start_month() const;
    int get_start_day() const;
    friend std::ostream& operator<<(std::ostream& os, const loan& loan1);
};


#endif //MAIN_CPP_LOAN_H
