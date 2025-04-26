//
// Created by ofekz on 3/11/2025.
//

#ifndef MAIN_CPP_RESERVATION_H
#define MAIN_CPP_RESERVATION_H

#include <string>
#include <iostream>
using std::string;

class reservation {
    string ISBN;
    int start_day;
    int start_month;
    int start_year;
    int days_since_2000;
public:
    reservation(string ISBN,int start_day,int start_month,int start_year);
    ~reservation()=default;
    int get_days_count() const;
    string get_ISBN() const;
    int getStartDay() const;
    int getStartMonth() const;
    int getStartYear() const;
    friend std::ostream& operator<<(std::ostream& os, const reservation& res1);
};

static int days_from_2000(int day, int month, int year);

#endif //MAIN_CPP_RESERVATION_H
