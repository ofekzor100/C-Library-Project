#ifndef OOPLIB_LIBRARY_H
#define OOPLIB_LIBRARY_H

#include "user.h"
#include "librarian.h"
#include "loaner.h"
#include "book.h"
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include<vector>
using std::vector;
#include <set>
using std::set;
#include "Exceptions.h"
#include "RSA.h"

typedef struct {
    int day;
    int month;
    int year;
}date;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class library{
    date today;
    vector<user*> users;
    vector<book*> books;
    set<string> categories;
    static int MaxLoans;
    RSA encoding;
public:

    library();
    ~library();

    friend class librarian;

    template<class T>
    void create_vector_users(string fileName);
    void create_vector_books(string fileName);

    void Copy_books_to_database();
    void Copy_users_to_dataset(string librariansFile, string loanersFile);

    string user_verify(bool& is_librarian, string id,string password);
    string create_librarian(string id);

    void loans_and_reservations_preperation( vector<book*>& books);

    void printBook(const string& ISBN);
    void printBooksByCategory(const string& category);
    void search( const string& id, const string& searchText);
    void update(const string& id);

    void addBook();
    void updateBook();
    void removeBook(const string& ISBN);
    void addClient();
    void removeClient(const string& id);
    void addCategory(const string& category);
    void removeCategory(const string& category);
    static void setMaxLoans(int numLoans);
    static int  getmaxloans();

    void Loan(const string& id,const string& argument);
    void ReturnBook(const string& id,const string& argument);
    void ReserveSecretly(const string& id);
    void CancelReservation(const string& id,const string& argument);
    void PrintLoans(const string& id);
    void PrintReservations(const string& id);
    void PrintHistory(const string& id);

    void Restore_Password();

};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void library::create_vector_users(string fileName) {
    ifstream file_in(fileName); // Open the CSV file
    if (!file_in) {
        throw CanNotOpenFile();
    }

    string line;
    while (std::getline(file_in, line)) {
        std::stringstream ss(line);
        string id, name, password;

        // Read values separated by commas
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, password, ',');

        T* new_user = new T(id,name,password);
        this->users.push_back(new_user);
    }
}



#endif //OOPLIB_LIBRARY_H
