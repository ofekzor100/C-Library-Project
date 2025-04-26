//
// Created by ofekz on 3/11/2025.
//

#include "loan.h"

loan::loan(string ISBN, int start_day, int start_month, int start_year, int end_day, int end_month, int end_year):ISBN(ISBN),start_day(start_day),start_month(start_month),start_year(start_year)
        ,end_day(end_day),end_month(end_month),end_year(end_year) {

}

int loan::get_end_year() const {
    return this->end_year;
}

int loan::get_end_month() const {
    return this->end_month;
}

int loan::get_end_day() const {
    return this->end_day;
}

string loan::get_ISBN() const {
    return this->ISBN;
}

int loan::get_start_year() const {
    return this->start_year;
}

int loan::get_start_month() const {
    return this->start_month;
}

int loan::get_start_day() const {
    return this->start_day;
}

std::ostream &operator<<(std::ostream &os, const loan &loan1) {
    os<<"Book ISBN: "<<loan1.ISBN<<std::endl;
    os<<"The loan started on :"<<loan1.start_day<<"."<<loan1.start_month<<"."<<loan1.start_year<<std::endl;
    os<<"The loan ends on :"<<loan1.end_day<<"."<<loan1.end_month<<"."<<loan1.end_year;
    return os;
}
