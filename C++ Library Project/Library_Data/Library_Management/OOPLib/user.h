//
// Created by ofekz on 3/10/2025.
//

#ifndef OOPLIB_USER_H
#define OOPLIB_USER_H

#include <iostream>
#include <string>
#include <fstream>
#include<vector>
#include "book.h"
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;

/////////forward declaration
class library;

class user {
    string id;
    string name;
    string password;
public:
    user()=default ;
    user(string id,string name,string password);
    virtual ~user(){};
    string getId() const ;
    string getName() const ;
    string getPassword() const ;
    void setId(const string& id);
    void setName(const string& id);
    void setPassword(const string& id);
    virtual void prepare(const library& lib,vector<book*>& books,int day,int month,int year,int days_count,int max_loans) = 0 ;
    virtual void search_info(const library& lib,bool found, string searchText,string bookName, string bookISBN, bool& found_loaner) = 0 ;
    virtual  std::ostream& operator<<(std::ostream& os) =0;



};


#endif //OOPLIB_USER_H
