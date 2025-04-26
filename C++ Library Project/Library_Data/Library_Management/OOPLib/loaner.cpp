//
// Created by ofekz on 3/10/2025.
//

#include "loaner.h"
#include <string>
#include <sstream>
using std::string;
#include "Exceptions.h"
#include "library.cpp"


loaner::loaner(string id,string name,string password):user(id,name,password),loan_historys(),loans(),reservations(),total_loans(0) {
    string loaner_id = this->getId();
    string loaner_file = loaner_id + "_loanHistory.csv";
    string fileName_historys =
            "C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/" +
            loaner_file;
    string fileName_loans="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/"
            +loaner_id+"_loans.csv";
    string fileName_reservations="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/"
                                 +loaner_id+"_reservations.csv";
    create_vector_loan_historys_or_loans(0,fileName_historys);
    create_vector_loan_historys_or_loans(1,fileName_loans);
    create_vector_reservations(fileName_reservations);
}

loaner::~loaner() {
    Copy_reservations_to_database();
    Copy_loans_to_dataset();
    Copy_loanHistorys_to_dataset();
    for(auto lh:loan_historys){
        delete lh;
    }
    loan_historys.clear();

    for(auto ln:loans){
        delete ln;
    }
    loans.clear();

    for(auto rs:reservations){
        delete rs;
    }
    reservations.clear();
}

void loaner::create_vector_loan_historys_or_loans(const bool& isLoans,string fileName) {
    // Check if file exists, if not, create an empty file
    std::ifstream file_check(fileName);
    if (!file_check) {  // File doesn't exist
        std::ofstream file_out(fileName);  // Create the file
        if (!file_out) {
            throw CanNotCreateFile();
        }
        file_out.close();
    }
    file_check.close();
    ifstream file_in(fileName); // Open the CSV file
    if (!file_in) {
        throw CanNotOpenFile();
    }

    string line;
    while (std::getline(file_in, line)) {
        std::stringstream ss(line);
        string ISBN, start_date, end_date;

        // Read values separated by commas
        std::getline(ss, ISBN, ',');
        std::getline(ss, start_date, ',');
        std::getline(ss, end_date, ',');

        // Parse start_date (e.g., "21.3.2025")
        int start_day, start_month, start_year;
        char dot1, dot2; // To store the '.' separators

        std::stringstream date_stream(start_date);  // Use correct variable
        date_stream >> start_day >> dot1 >> start_month >> dot2 >> start_year;

        // Parse end_date (e.g., "21.3.2025")
        int end_day, end_month, end_year;
        char dot3, dot4; // To store the '.' separators

        std::stringstream date_stream2(end_date);  // Use correct variable
        date_stream2 >> end_day >> dot3 >> end_month >> dot4 >> end_year;

        // Validate if parsing was successful for both start and end dates
        if (dot1 != '.' || dot2 != '.' || dot3 != '.' || dot4 != '.') {
            std::cerr << "Error: Invalid date format in file for loan history." << std::endl;
            continue;  // Skip invalid entries
        }

        if(!isLoans){
            loan_history *new_loan_history = new loan_history(ISBN, start_day, start_month, start_year, end_day, end_month, end_year);
                this->loan_historys.push_back(new_loan_history);
        }
        else{
            loan *new_loan = new loan(ISBN, start_day, start_month, start_year, end_day, end_month, end_year);
            this->loans.push_back(new_loan);
            this->total_loans++;
        }

    }
}

void loaner::create_vector_reservations(string fileName) {
    // Check if file exists, if not, create an empty file
    std::ifstream file_check(fileName);
    if (!file_check) {  // File doesn't exist
        std::ofstream file_out(fileName);  // Create the file
        if (!file_out) {
            throw CanNotCreateFile();
        }
        file_out.close();
    }
    file_check.close();
    ifstream file_in(fileName); // Open the CSV file
    if (!file_in) {
        throw CanNotOpenFile();
    }

    string line;
    while (std::getline(file_in, line)) {
        std::stringstream ss(line);
        string ISBN, start_date;

        // Read values separated by commas
        std::getline(ss, ISBN, ',');
        std::getline(ss, start_date, ',');

        // Parse start_date (e.g., "21.3.2025")
        int start_day, start_month, start_year;
        char dot1, dot2; // To store the '.' separators

        std::stringstream date_stream(start_date);  // Use correct variable
        date_stream >> start_day >> dot1 >> start_month >> dot2 >> start_year;

        reservation *new_reservation = new reservation(ISBN, start_day, start_month, start_year);
        reservations.push_back(new_reservation);
    }
}


void loaner::prepare( const library& lib,vector<book*>& books,int day,int month,int year,int days_count,int max_loans) {
    for (auto it = loans.begin(); it != loans.end();) {
        int endYear = (*it)->get_end_year();
        int endMonth = (*it)->get_end_month();
        int endDay = (*it)->get_end_day();
        int startDay= (*it)->get_start_day();
        int startMonth= (*it)->get_start_month();
        int startYear= (*it)->get_start_year();
        string ISBN=(*it)->get_ISBN();

        if (endYear < year || (endYear == year && endMonth <month) ||
            (endYear == year && endMonth == month && endDay < day)) {

            for(int j=0;j<books.size();j++){
                if((*it)->get_ISBN()==books[j]->getISBN()){
                    books[j]->incQuantity();
                    break;
                }
            }

            loan_history* new_hist=new loan_history(ISBN,startDay,startMonth,startYear,endDay,endMonth,endYear);
            loan_historys.push_back(new_hist);
            it = loans.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = reservations.begin(); it != reservations.end();)
    {
        int days_count_reservation=(*it)->get_days_count();
        if(days_count-days_count_reservation>7){
            it = reservations.erase(it);
            continue;
        }
        else{
            ++it;
        }
    }
}



void loaner::remove_book_from_loaners_loans_and_reservations(const string& ISBN) {
    for(vector<loan*>::iterator it=loans.begin();it!=loans.end();){
        if((*it)->get_ISBN()==ISBN){
            loan_history* new_hist=new loan_history(ISBN,(*it)->get_start_day(),(*it)->get_start_month(),(*it)->get_start_year()
                    ,get_current_date()[0],get_current_date()[1],get_current_date()[2]);
            delete *it;
            loan_historys.push_back(new_hist);
            it=loans.erase(it);
        }
        else{
            ++it;
        }
    }

    for(vector<reservation*>::iterator it=reservations.begin();it!=reservations.end();){
        if((*it)->get_ISBN()==ISBN){
            delete *it;
            it=reservations.erase(it);
        }
        else{
            ++it;
        }
    }
}

int loaner::getTotalLoans() {
    return this->total_loans;
}

void loaner::add_to_loans(const string& ISBN,int start_day,int start_month,int start_year,
                          int end_day,int end_month,int end_year) {
    loan* new_loan= new loan(ISBN,start_day,start_month,start_year,end_day,end_month,end_year);
    loans.push_back(new_loan);
    total_loans++;
    std::cout<<"Book added to loans successfully!"<<std::endl<<std::endl;
}

void loaner::add_to_reservations(const string &ISBN, int start_day, int start_month, int start_year) {
    reservation* new_reservation= new reservation(ISBN,start_day,start_month,start_year);
    reservations.push_back(new_reservation);
}

void loaner::reservations_to_loans_(vector<book *> &books, int day, int month, int year, int max_loans) {

    for (auto it = reservations.begin(); it != reservations.end();it++) {
        book* reserved_book=nullptr;
        for(int i=0;i<books.size();i++){
            if(books[i]->getISBN()==(*it)->get_ISBN()){
                reserved_book=books[i];
                break;
            }
        }
        assert(reserved_book);
        if (this->getTotalLoans() < max_loans && reserved_book->getQuantity() > 0) {
            int end_day, end_month, end_year;
            std::cout << "The reserved book: " << reserved_book->getName() <<" is availible for loan!"<< std::endl;
            std::cout << "To loan the book,press Y.To continue,press any other string."<< std::endl;
            string input;
            std::cin>>input;
            if(input!="Y")
            {
                continue;
            }
            std::cout << "Max duration for the  loan:" << reserved_book->getDuration() << std::endl;
            std::cout << "Please enter date to end the loan:" << std::endl;
            std::cout << "Day:" ;
            std::cin >> end_day;
            std::cout << "Month:" ;
            std::cin >> end_month;
            std::cout << "Year:" ;
            std::cin >> end_year;
            if (days_from_2000(end_day, end_month, end_year) - days_from_2000(day, month, year) >
                reserved_book->getDuration()) {
                throw TooLongDuration();
            }
            if (days_from_2000(end_day, end_month, end_year) < days_from_2000(day, month, year)) {
                throw InvalidDate();
            }
            this->add_to_loans(reserved_book->getISBN(), day, month, year, end_day, end_month, end_year);
           // it=reservations.erase(it);
            reserved_book->decQuantity();
        }

    }
}

bool loaner::finish_loan(const string &ISBN) {
    for(vector<loan*>::iterator it=loans.begin();it!=loans.end();++it){
        if((*it)->get_ISBN()==ISBN){
            loan_history* new_hist=new loan_history(ISBN,(*it)->get_start_day(),(*it)->get_start_month(),(*it)->get_start_year()
                    ,get_current_date()[0],get_current_date()[1],(get_current_date()[2]));
            loan_historys.push_back(new_hist);
            this->total_loans--;
            delete *it;
            loans.erase(it);
            std::cout<< "Book returned successfully!"<<std::endl<<std::endl;
            return 1;
        }
    }
    throw BookNotLoaned();
}

bool loaner::cancel_reservation(const string &ISBN) {
    for(vector<reservation*>::iterator it=reservations.begin();it!=reservations.end();++it){
        if((*it)->get_ISBN()==ISBN){
            delete *it;
            reservations.erase(it);
            std::cout<< "Reservation canceled successfully!"<<std::endl<<std::endl;
            return 1;
        }
    }
    throw BookNotReserved();
}

std::ostream &loaner::operator<<(std::ostream &os) {
    os<<"Loaner name: "<<this->getName()<<std::endl;
    os<<"Loaner id: "<<this->getId()<<std::endl;
    os<<"Loaner loan history: "<<std::endl;
    os<<"--------------------------------------------------------- "<<std::endl;
    for(int i=0;i<loan_historys.size();i++){
        os<<loan_historys[i];
    }
    std::cout<<std::endl;
    os<<"Loaner loans: "<<std::endl;
    os<<"--------------------------------------------------------- "<<std::endl;
    for(int i=0;i<loans.size();i++){
        os<<loans[i];
    }
    std::cout<<std::endl;
    os<<"Loaner reservations: "<<std::endl;
    os<<"--------------------------------------------------------- "<<std::endl;
    for(int i=0;i<reservations.size();i++){
        os<<reservations[i];
    }
    std::cout<<std::endl;
    return os;
}

void loaner::printLoans() {
    std::cout<<"Loaner loans: "<<std::endl;
    std::cout<<"--------------------------------------------------------- "<<std::endl;
    for(int i=0;i<loans.size();i++){
        std::cout<<*(loans[i])<<std::endl<<std::endl;

    }
    std::cout<<std::endl<<std::endl;
}

void loaner::printLoanHistory() {
    std::cout<<"Loaner loan history: "<<std::endl;
    std::cout<<"--------------------------------------------------------- "<<std::endl;
    for(int i=0;i<loan_historys.size();i++){
        std::cout<<*(loan_historys[i])<<std::endl<<std::endl;
    }
    std::cout<<std::endl<<std::endl;
}

void loaner::printReservations() {
    std::cout<<"Loaner reservations: "<<std::endl;
    std::cout<<"--------------------------------------------------------- "<<std::endl;
    for(int i=0;i<reservations.size();i++){
        std::cout<<*(reservations[i])<<std::endl<<std::endl;
    }
    std::cout<<std::endl<<std::endl;
}

void loaner::search_info(const library &lib, bool found, string searchText, string bookName, string bookISBN, bool& found_loaner) {
    if(!found){
        return;
    }
    for (int i = 0; i < loan_historys.size(); i++) {
        if (loan_historys[i]->getISBN().compare(bookISBN) == 0 ) {
            std::cout << "This book  has been loaned "<<std::endl;
            std::cout << "His loan ended on : "<<std::endl;
            std::cout << loan_historys[i]->getEndDay()<<"."<<loan_historys[i]->getEndMonth()<<"."<<loan_historys[i]->getEndYear() << std::endl;
            std::cout << "---------------------------------------"<<std::endl;
        }
    }
    for (int i = 0; i < loans.size(); i++) {
        if (loans[i]->get_ISBN().compare(bookISBN) == 0 ) {
            std::cout << "This book is in loan : "<<std::endl;
            std::cout << "His loan ends on : "<<std::endl;
            std::cout << loans[i]->get_end_day()<<"."<<loans[i]->get_end_month()<<"."<<loans[i]->get_end_year() << std::endl;
            std::cout << "---------------------------------------"<<std::endl;
        }
    }
    for (int i = 0; i < reservations.size(); i++) {
        if (reservations[i]->get_ISBN().compare(bookISBN) == 0 ) {
            std::cout << "This book is in reservation : "<<std::endl;
            std::cout << "Reserved on date : "<<std::endl;
            std::cout << reservations[i]->getStartDay()<<"."<<reservations[i]->getStartMonth()<<"."<<reservations[i]->getStartYear() << std::endl;
            std::cout << "---------------------------------------"<<std::endl;
        }
    }
    std::cout<<std::endl;
}

void loaner::Copy_reservations_to_database() {
    string file="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/"
                "Library_Data/Library_Directory/"+this->getId()+"_reservations.csv";
    std::ofstream file_out(file);
    if (!file_out) {
        throw CanNotOpenFile();
    }

    for (const auto& reservation : reservations) {
        file_out << reservation->get_ISBN() << ","
                 << reservation->getStartDay() << "."
                 << reservation->getStartMonth() << "."
                 << reservation->getStartYear() << "\n";
    }

    file_out.close();
}

void loaner::Copy_loans_to_dataset() {
    string file="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/"
                "Library_Data/Library_Directory/"+this->getId()+"_loans.csv";
    std::ofstream file_out(file);
    if (!file_out) {
        throw CanNotOpenFile();
    }

    for (const auto& loan : loans) {
        file_out << loan->get_ISBN() << ","
                 << loan->get_start_day() << "."
                 << loan->get_start_month() << "."
                 << loan->get_start_year() << ","
                 << loan->get_end_day() << "."
                 << loan->get_end_month() << "."
                 << loan->get_end_year() << "\n";
    }

    file_out.close();
}

void loaner::Copy_loanHistorys_to_dataset() {
    string file="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/"
                "Library_Data/Library_Directory/"+this->getId()+"_loanHistory.csv";
    std::ofstream file_out(file);
    if (!file_out) {
        throw CanNotOpenFile();
    }

    for (const auto& loan : loan_historys) {
        file_out << loan->getISBN() << ","
                 << loan->getStartDay() << "."
                 << loan->getStartMonth() << "."
                 << loan->getStartYear() << ","
                 << loan->getEndDay() << "."
                 << loan->getEndMonth() << "."
                 << loan->getEndYear() << "\n";
    }

    file_out.close();
}





