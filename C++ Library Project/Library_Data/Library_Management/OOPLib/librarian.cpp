//
// Created by ofekz on 3/10/2025.
//

#include "librarian.h"
#include "library.h"

librarian::librarian(string id, string name, string password) : user(id, name, password) {

}


void librarian::prepare(const library& lib,vector<book*>& books,int day,int month,int year,int days_count,int max_loans) {
    for(int i=0;i<lib.users.size();i++){
        if(typeid(*lib.users[i])==typeid(loaner)){
            lib.users[i]->prepare(lib,books,day,month,year,days_count,max_loans);
        }
    }
}

std::ostream &librarian::operator<<(std::ostream &os) {
    os<<"Librarian name: "<<this->getName()<<std::endl;
    os<<"Librarian id: "<<this->getId()<<std::endl;
    return os;
}

void librarian::search_info(const library &lib, bool found, string searchText, string bookName, string bookISBN, bool& found_loaner) {
    for (int i = 0; i < lib.users.size(); i++) {
        if (lib.users[i]->getName() == searchText || lib.users[i]->getId() == searchText) {
            found_loaner=true;
            std::cout << "Found loaner: " << std::endl;
            std::cout << " ID       : " << lib.users[i]->getId() << std::endl;
            std::cout << " Name       : " << lib.users[i]->getName() << std::endl;
            std::cout << "---------------------------------------" << std::endl;


        }
    }
    if(found) {

        for (int i = 0; i < lib.users.size(); i++) {
            loaner *current = dynamic_cast<loaner *>(lib.users[i]);
            if (current == nullptr) {
                continue;
            }
            std::cout << "Book " << bookName << " data for the Loaner: " << current->getName()
                      << std::endl;
            std::cout << "---------------------------------------" << std::endl;
            current->search_info(lib,found,searchText,bookName, bookISBN,found_loaner);
            std::cout << "---------------------------------------" << std::endl;
            std::cout << std::endl;
        }
    }
    std::cout<<std::endl;
}




