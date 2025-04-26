//
// Created by ofekz on 3/10/2025.
//

#ifndef OOPLIB_LOANER_H
#define OOPLIB_LOANER_H

#include "user.h"
#include "loan.h"
#include "loan_history.h"
#include "reservation.h"


class loaner: public user {
    vector<loan_history*> loan_historys;
    int total_loans;
    vector<loan*> loans;
    vector<reservation*> reservations;
public:
    loaner(string id,string name,string password);
    ~loaner();

    friend class librarian;

    void create_vector_loan_historys_or_loans(const bool& isLoans,string fileName);
    void create_vector_reservations(string fileName);
    void Copy_reservations_to_database();
    void Copy_loans_to_dataset();
    void Copy_loanHistorys_to_dataset();

    void prepare( const library& lib,vector<book*>& books,int day,int month,int year,int days_count,int max_loans) override;

    void search_info(const library& lib,bool found, string searchText,string bookName, string bookISBN, bool& found_loaner) override;

    void remove_book_from_loaners_loans_and_reservations(const string& ISBN);
    int getTotalLoans();
    void add_to_loans(const string& ISBN,int start_day,int start_month,int start_year,
                      int end_day,int end_month,int end_year);
    void add_to_reservations(const string& ISBN,int start_day,int start_month,int start_year);
    void reservations_to_loans_(vector<book*>& books,int day,int month,int year,int max_loans );
    bool finish_loan(const string& ISBN);
    bool cancel_reservation(const string& ISBN);
    std::ostream& operator<<(std::ostream& os) override;
    void printLoans();
    void printLoanHistory();
    void printReservations();
};

#endif //OOPLIB_LOANER_H
