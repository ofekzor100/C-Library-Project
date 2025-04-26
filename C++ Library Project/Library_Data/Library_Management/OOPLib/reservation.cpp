//
// Created by ofekz on 3/11/2025.
//

#include "reservation.h"
#include <iostream>
#include <chrono>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

reservation::reservation(string ISBN, int start_day, int start_month, int start_year) :
ISBN(ISBN),start_day(start_day),start_month(start_month),start_year(start_year),days_since_2000(0){
this->days_since_2000= days_from_2000(this->start_day,this->start_month,this->start_year);
}

int reservation::get_days_count() const{
   return this->days_since_2000;
}

string reservation::get_ISBN() const {
    return this->ISBN;
}

int reservation::getStartDay() const {
    return this->start_day;
}

int reservation::getStartMonth() const {
    return this->start_month;
}

int reservation::getStartYear() const {
    return this->start_year;
}

std::ostream &operator<<(std::ostream &os, const reservation &res1) {
    os<<"Book ISBN: "<<res1.ISBN<<std::endl;
    os<<"The reservation started on :"<<res1.start_day<<"."<<res1.start_month<<"."<<res1.start_year<<std::endl;
    return os;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  static int days_from_2000(int day, int month, int year) {
    std::tm start = {};
    std::tm current = {};

    start.tm_mday = 1;
    start.tm_mon = 0;  // January (0-based)
    start.tm_year = 100; // Year 2000 (years since 1900)

    current.tm_mday = day;
    current.tm_mon = month - 1; // Convert to 0-based
    current.tm_year = year - 1900;

    std::time_t start_time = std::mktime(&start);
    std::time_t current_time = std::mktime(&current);

    return std::difftime(current_time, start_time) / (60 * 60 * 24); // Convert seconds to days
}
