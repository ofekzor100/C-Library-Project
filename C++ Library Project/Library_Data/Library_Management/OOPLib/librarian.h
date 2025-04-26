//
// Created by ofekz on 3/10/2025.
//

#ifndef OOPLIB_LIBRARIAN_H
#define OOPLIB_LIBRARIAN_H

#include "user.h"


class librarian: public user {
public:
    librarian(std::string id,string name,string password);
    ~librarian(){};
    void prepare(const library& lib,vector<book*>& books,int day,int month,int year,int days_count,int max_loans) override;
    void search_info(const library& lib,bool found, string searchText,string bookName, string bookISBN, bool& found_loaner) override;

    std::ostream& operator<<(std::ostream& os) override;
};



#endif //OOPLIB_LIBRARIAN_H
