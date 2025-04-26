//
// Created by ofekz on 3/11/2025.
//

#ifndef MAIN_CPP_BOOK_H
#define MAIN_CPP_BOOK_H
#include <iostream>
#include <string>
#include <fstream>
#include "assert.h"
#include<vector>
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;

class book {
    string ISBN;
    string name;
    string author;
    int year;
    string category;
    int quantity;
    int duration;
public:
    book(string ISBN, string name, string author, int year, string category, int quantity, int duration);
    ~book()=default;
    string getISBN();
    string getName();
    string getAuthor();
    int getYear();
    string getcategory();
    int getQuantity();
    int getDuration();
    void setName(string name);
    void setAuthor(string author);
    void setYear(int year);
    void setCategory(string category);
    void setQuantity(int quantity);
    void incQuantity();
    void decQuantity();
    void setDuration(int duration);
};


#endif //MAIN_CPP_BOOK_H
