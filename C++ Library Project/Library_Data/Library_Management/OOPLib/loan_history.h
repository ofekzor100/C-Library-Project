//
// Created by ofekz on 3/11/2025.
//

#ifndef MAIN_CPP_LOAN_HISTORY_H
#define MAIN_CPP_LOAN_HISTORY_H
#include <string>
#include <iostream>
using std::string;


class loan_history {
    string ISBN;
    int start_day;
    int start_month;
    int start_year;
    int end_day;
    int end_month;
    int end_year;
public:
    loan_history(string ISBN,int start_day,int start_month,int start_year,int end_day,int end_month,int end_year);
    ~loan_history()=default;
    string getISBN() const;
    int getStartDay() const;
    int getStartMonth() const;
    int getStartYear() const;
    int getEndDay() const;
    int getEndMonth() const;
    int getEndYear() const;
    friend std::ostream& operator<<(std::ostream& os, const loan_history& loanhist1);
};


#endif //MAIN_CPP_LOAN_HISTORY_H
