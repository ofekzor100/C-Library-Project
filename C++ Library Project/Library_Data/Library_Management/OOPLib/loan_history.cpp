//
// Created by ofekz on 3/11/2025.
//

#include "loan_history.h"

loan_history::loan_history(string ISBN, int start_day, int start_month, int start_year, int end_day, int end_month,
                           int end_year):ISBN(ISBN),start_day(start_day),start_month(start_month),start_year(start_year)
                           ,end_day(end_day),end_month(end_month),end_year(end_year){
}

string loan_history::getISBN() const {
    return this->ISBN;
}

int loan_history::getEndDay() const {
    return this->end_day;
}

int loan_history::getEndMonth() const {
    return this->end_month;
}

int loan_history::getEndYear() const {
    return this->end_year;
}

std::ostream &operator<<(std::ostream &os, const loan_history &loanhist1) {
    os<<"Book ISBN: "<<loanhist1.ISBN<<std::endl;
    os<<"The loan started on :"<<loanhist1.start_day<<"."<<loanhist1.start_month<<"."<<loanhist1.start_year<<std::endl;
    os<<"The loan ended on :"<<loanhist1.end_day<<"."<<loanhist1.end_month<<"."<<loanhist1.end_year;
    return os;
}

int loan_history::getStartDay() const {
    return this->start_day;
}

int loan_history::getStartMonth() const {
    return this->start_month;
}

int loan_history::getStartYear() const {
    return this->start_year;
}
