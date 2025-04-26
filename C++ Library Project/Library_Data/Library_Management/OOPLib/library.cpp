#include "library.h"

#include <iostream>
#include <algorithm>
#include "assert.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int* get_current_date();
static int days_from_2000(int day, int month, int year);
void deleteFilesOfLoaner(const string& id);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int library::MaxLoans=getmaxloans();

library::library():users(),books() ,categories(),encoding() {
    today.day=get_current_date()[0];
    today.month=get_current_date()[1];
    today.year=get_current_date()[2];
    std::cout << "Current Date: " << today.day<<"-"<<today.month <<"-"<<today.year<< std::endl;  // Debugging line
    create_vector_users<librarian>("C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/Librarians.csv");
    create_vector_users<loaner>("C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/Loaners.csv");
    create_vector_books("C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/Books.csv");
    loans_and_reservations_preperation(books);
}

library::~library() {
    Copy_books_to_database();
    Copy_users_to_dataset("C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/"
                          "C++ Library Project/Library_Data/Library_Directory/Librarians.csv",
                          "C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/"
                          "C++ Library Project/Library_Data/Library_Directory/Loaners.csv");
    for(auto user:users){
        delete user;
    }
    users.clear();

    for(auto book:books){
        delete book;
    }
    books.clear();
}


string library::user_verify(bool& is_librarian,string id,string password) {


    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            if (users[i]->getPassword() != password) {
                throw WrongPassword();
            }
            std::cout<<"Hello "<<users[i]->getName()<<"!"<<std::endl;
            if(typeid(*users[i])== typeid(librarian)){
                is_librarian=true;
            }
            else{
                loaner* current_loaner=dynamic_cast<loaner*>(users[i]);
                current_loaner->reservations_to_loans_(books,today.day,today.month,today.year,MaxLoans);
            }
            return users[i]->getName();
        }
    }
    throw UserNotFound();
}


string library::create_librarian(string id) {
    string password;
    string name;
    std::cout << "Please enter name:" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Please enter password:" << std::endl;
    std::getline(std::cin, password);

    librarian* new_librarian=new librarian(id,name,password);
    new_librarian->setPassword(password);
    new_librarian->setName(name);
    new_librarian->setId(id);
    users.push_back(new_librarian);
    return name;
}


void library::create_vector_books(string fileName) {
    ifstream file_in(fileName); // Open the CSV file
    if (!file_in) {
        throw CanNotOpenFile();
    }

    string line;
    while (std::getline(file_in, line)) {
        std::stringstream ss(line);
        string ISBN, name, author,category;
        string year,quantity,duration;

        // Read values separated by commas
        std::getline(ss, ISBN, ',');
        std::getline(ss, name, ',');
        std::getline(ss, author, ',');
        std::getline(ss, year, ',');
        std::getline(ss, category, ',');
        std::getline(ss, quantity, ',');
        std::getline(ss, duration, ',');

        book* new_book = new book(ISBN,name,author,std::stoi(year),category,std::stoi(quantity),std::stoi(duration));

        categories.insert(category);

        this->books.push_back(new_book);
    }

}

void library::Copy_books_to_database() {
    std::ofstream file_out("C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/Books.csv");
    if (!file_out) {
        throw CanNotOpenFile();
    }

    for (const auto& book : books) {
        file_out << book->getISBN() << ","
                 << book->getName() << ","
                 << book->getAuthor() << ","
                 << book->getYear() << ","
                 << book->getcategory() << ","
                 << book->getQuantity() << ","
                 << book->getDuration() << "\n";
    }

    file_out.close();
}

void library::Copy_users_to_dataset(string librariansFile, string loanersFile) {
    std::ofstream librarians_out(librariansFile);
    std::ofstream loaners_out(loanersFile);
    if (!librarians_out || !loaners_out) {
        throw CanNotOpenFile();
    }

    for (const auto& user : users) {
        if (dynamic_cast<librarian*>(user)) {
            librarians_out << user->getId() << ","
                           << user->getName() << ","
                           << user->getPassword() << "\n";
        } else if (dynamic_cast<loaner*>(user)) {
            loaners_out << user->getId() << ","
                        << user->getName() << ","
                        << user->getPassword() << "\n";
        }
    }

    librarians_out.close();
    loaners_out.close();
}

void library::loans_and_reservations_preperation( vector<book*>& books) {
    for(int i=0;i<users.size();i++) {
        users[i]->prepare(*this,books, this->today.day, this->today.month, this->today.year,
                          days_from_2000(today.day, today.month, today.year), MaxLoans);
    }
}


void library::printBook(const string& ISBN) {
    std::cout << "---------------------------------------"<<std::endl;
    std::cout << " Searching for book with ISBN: " << ISBN <<std::endl;
    std::cout << "---------------------------------------"<<std::endl<<std::endl;

    for (int i = 0; i < books.size(); i++) {
        if (books[i]->getISBN() == ISBN) {
            std::cout << "Book Details:"<<std::endl;
            std::cout << "---------------------------------------"<<std::endl;
            std::cout << " Title       : " << books[i]->getName() << std::endl;
            std::cout << " Author      : " << books[i]->getAuthor() << std::endl;
            std::cout << " Year        : " << books[i]->getYear() << std::endl;
            std::cout << " Category    : " << books[i]->getcategory() << std::endl;
            std::cout << " Quantity    : " << books[i]->getQuantity() <<std::endl;
            std::cout << " Max Duration: " << books[i]->getDuration() <<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
            return;
        }
    }
    // If book is not found
   throw BookNotFound();
}


void library::printBooksByCategory(const std::string& category) {
    std::cout << "---------------------------------------"<<std::endl;
    std::cout << "Printing books in category: " << category <<std::endl;
    std::cout << "---------------------------------------"<<std::endl<<std::endl;
    string more_command;
    int sum_of_books_of_category=0;
    int index=0;
    while(1) {
        for (; index < books.size(); index++) {
            if (books[index]->getcategory() == category) {
                sum_of_books_of_category++;
                std::cout << "Book Details:" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << " ISBN       : " << books[index]->getISBN() << std::endl;
                std::cout << " Title       : " << books[index]->getName() << std::endl;
                std::cout << " Author      : " << books[index]->getAuthor() << std::endl;
                std::cout << " Year        : " << books[index]->getYear() << std::endl;
                std::cout << " Quantity    : " << books[index]->getQuantity() << std::endl;
                std::cout << " Max Duration: " << books[index]->getDuration() << std::endl;
                std::cout << "---------------------------------------" << std::endl << std::endl;
            }
            if (sum_of_books_of_category %10==0 &&sum_of_books_of_category!=0) {
                break;
            }
        }
        if(index==books.size()){
            throw NoMoreBooks();
        }

        std::cout << "To show more books please enter 'More',or  enter other string to finish "  <<std::endl;
        std::cin >>more_command;
        if(more_command!="More"){
            break;
        }
        index++;

    }
}



void library::search( const string& id,const std::string& searchText) {
    if(searchText.empty())
    {
        std::cout << " Please enter string to search " << searchText <<std::endl<<std::endl;
        return;
    }
    std::cout << "---------------------------------------"<<std::endl;
    std::cout << " Searching for string: " << searchText <<std::endl;
    std::cout << "---------------------------------------"<<std::endl<<std::endl;

    bool found_category=false;
    bool found_author=false;
    bool found_name=false;
    bool found_ISBN=false;
    bool found_loaner=false;

    string book_name;
    string book_ISBN;
    for (int i = 0; i < books.size(); i++) {


        if (books[i]->getISBN().compare(searchText) == 0 && !found_ISBN){
            found_ISBN= true;
            book_name=books[i]->getName();
            book_ISBN=books[i]->getISBN();
            std::cout << "Found book ISBN : "<<std::endl;
            std::cout << " ISBN       : " << books[i]->getISBN() << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        if(books[i]->getName().compare(searchText) == 0 && !found_name){
            book_name=books[i]->getName();
            book_ISBN=books[i]->getISBN();
            found_name=true;
            std::cout << "Found book name : "<<std::endl;
            std::cout << " Name       : " << books[i]->getName() << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        if(books[i]->getAuthor().compare(searchText) == 0 && !found_author){
            found_author=true;
            std::cout << "Found author : "<<std::endl;
            std::cout << " Name       : " << books[i]->getAuthor() << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        if(books[i]->getcategory().compare(0,searchText.size(),searchText) == 0 && !found_category){
            found_category=true;
            std::cout << "Found category : "<<std::endl;
            std::cout << " Category       : " << books[i]->getcategory() << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }

    }
        bool found=found_name || found_ISBN ;
        user* current=nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            current = (users[i]);
        }
    }

    current->search_info(*this,found,searchText,book_name,book_ISBN,found_loaner);

    // If search is not found
    if(!found_category && !found_author && !found_name && !found_ISBN && !found_loaner){
    throw SearchNotFound();
    }
}

void library::update(const std::string& id) {
    std::cout << "Please enter your new id,name,and password" << std::endl;
    string new_id, new_name, new_password;
    std::cout << "new id: " << std::endl;
    std::getline(std::cin, new_id);
    if(!(!new_id.empty() && std::all_of(new_id.begin(), new_id.end(), ::isdigit) )){
        throw NotValidId();
    }
    for(int j=0;j<users.size();j++){
        if(users[j]->getId()==new_id){
            continue;
        }
        if(users[j]->getId()==new_id){
            throw IdInUse();
        }
    }
    std::cout << "new name: " << std::endl;
    std::getline(std::cin, new_name);
    std::cout << "new password: " << std::endl;
    std::getline(std::cin, new_password);
    for(int i=0; i<users.size();i++) {
        if(users[i]->getId()==id ) {
            users[i]->setId(new_id);
            users[i]->setName(new_name);
            users[i]->setPassword(new_password);
            std::cout << " Updated succesfully!      : " << std::endl;
            std::cout << "---------------------------------------"<<std::endl;
            return;
        }
    }


}

void library::addBook() {
    string ISBN;
    string name;
    string author;
    string year;
    string category;
    string quantity;
    string duration;
    std::cout << "---------------------------------------"<<std::endl;
    std::cout << " Please enter book details: " << ISBN <<std::endl;
    std::cout << "---------------------------------------"<<std::endl<<std::endl;
    std::cout << "Please enter ISBN:" << std::endl;
    std::getline(std::cin, ISBN);
    if(!(!ISBN.empty() && std::all_of(ISBN.begin(), ISBN.end(), ::isdigit) && ISBN.size()==13)){
        throw InvalidISBN();
    }

    for (int i = 0; i < books.size(); i++) {
        if (books[i]->getISBN() == ISBN) {
            throw ISBNInUse();
        }
    }
    std::cout << "Please enter name:" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Please enter author:" << std::endl;
    std::getline(std::cin, author);
    std::cout << "Please enter year:" << std::endl;
    std::cin >> year;
    if( !(!year.empty() && std::all_of(year.begin(), year.end(), ::isdigit) ) ||  std::stoi(year)>this->today.year   ){
        throw InvalidYear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter category:" << std::endl;
    std::getline(std::cin, category);
    set<string>::iterator it;
    for (it = categories.begin(); it != categories.end(); ++it) {
        if((*it)==category){
            break;
        }
    }
    if(it==categories.end()){
        throw CategoryNotFound();
    }
    std::cout << "Please enter quantity:" << std::endl;
    std::cin >> quantity;
    if(!(!quantity.empty() && std::all_of(quantity.begin(), quantity.end(), ::isdigit) ) ||std::stoi(quantity)<0){
        throw InvalidQuantity();
    }
    std::cout << "Please enter duration:" << std::endl;
    std::cin >> duration;
    if(!(!duration.empty() && std::all_of(duration.begin(), duration.end(), ::isdigit) ) || std::stoi(duration)<0){
        throw InvalidDuration();
    }
    book* new_book= new book(ISBN,name,author,std::stoi(year),category,std::stoi(quantity),std::stoi(duration));
    this->books.push_back(new_book);
    std::cout << "Book added successfully !" << std::endl<<std::endl;
}

void library::updateBook() {
    string ISBN;
    string name;
    string author;
    string year;
    string category;
    string quantity;
    string duration;
    std::cout << "Please enter book ISBN to update:" << std::endl;
    std::getline(std::cin, ISBN);
    book* book_to_update;
    int i;
    for(i=0;i<books.size();i++){
        if(books[i]->getISBN()==ISBN){
            book_to_update=books[i];
            break;
        }
    }
    if(i==books.size()){
        throw BookNotFound();
    }

    std::cout << "Please enter name:" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Please enter author:" << std::endl;
    std::getline(std::cin, author);
    std::cout << "Please enter year:" << std::endl;
    std::cin >> year;
    if( !(!year.empty() && std::all_of(year.begin(), year.end(), ::isdigit) ) ||  std::stoi(year)>this->today.year   ){
        throw InvalidYear();
    }
    std::cout << "Please enter category:" << std::endl;
    std::cin >> category;
    set<string>::iterator it;
    for (it = categories.begin(); it != categories.end(); ++it) {
        if((*it)==category){
            break;
        }
    }
    if(it==categories.end()){
        throw CategoryNotFound();
    }
    std::cout << "Please enter quantity:" << std::endl;
    std::cin >> quantity;
    if(!(!quantity.empty() && std::all_of(quantity.begin(), quantity.end(), ::isdigit) ) ||std::stoi(quantity)<0){
        throw InvalidQuantity();
    }
    std::cout << "Please enter duration:" << std::endl;
    std::cin >> duration;
    if(!(!duration.empty() && std::all_of(duration.begin(), duration.end(), ::isdigit) ) || std::stoi(duration)<0){
        throw InvalidDuration();
    }
    book_to_update->setName(name);
    book_to_update->setAuthor(author);
    book_to_update->setCategory(category);
    book_to_update->setYear(std::stoi(year));
    book_to_update->setQuantity(std::stoi(quantity));
    book_to_update->setDuration(std::stoi(duration));
    std::cout << "Book updated successfully !" << std::endl<<std::endl;
}

void library::removeBook(const string &ISBN) {
    for(vector<book*>::iterator it=books.begin();it!=books.end();it++){
        if((*it)->getISBN()==ISBN){
            delete *it ;
            books.erase(it);
            for(int i=0;i<users.size();i++){
                if(typeid(*users[i])== typeid(loaner)){
                    dynamic_cast<loaner*>(users[i])->remove_book_from_loaners_loans_and_reservations(ISBN);
                }
            }
            std::cout << "Book removed successfully!" << std::endl<<std::endl;
            return;
        }
    }
    throw BookNotFound();
}

void library::addClient() {
    std::cout << "Please enter client's  id,name,and password" << std::endl;
    string id, name, password;
    std::cout << "id: " ;
    std::getline(std::cin, id);
    if(!(!id.empty() && std::all_of(id.begin(),id.end(), ::isdigit) )){
        throw NotValidId();
    }
    for(int j=0;j<users.size();j++){
        if(users[j]->getId()==id){
            throw IdInUse();
        }
    }
    std::cout << "name: " ;
    std::getline(std::cin,name);
    std::cout << "password: " ;
    std::getline(std::cin, password);
    loaner* new_loaner=new loaner(id,name,password);
    users.push_back(new_loaner);
    std::cout << "Client added successfully!" << std::endl<<std::endl;
}

void library::removeClient(const string &id) {
    for(vector<user*>::iterator it=users.begin();it!=users.end();it++){
        if((*it)->getId()==id){
            if(dynamic_cast<librarian*>(*it)!=nullptr)
            {
                throw DontRemoveOtherLibrarian();
            }
            delete *it ;
            users.erase(it);
            std::cout << "client removed successfully!" << std::endl<<std::endl;
            deleteFilesOfLoaner(id);
            return;
        }
    }
    throw ClientNotFound();
}

void library::addCategory(const string &category) {
    if(category.empty()){
        throw InvalidCategory();
    }
    categories.insert(category);
    std::cout << "Category added successfully!" << std::endl<<std::endl;
}

void library::removeCategory(const string &category) {
    set<string>::iterator it1;
    for( it1=categories.begin();it1!=categories.end();it1++){
        if((*it1)==category) {
            break;
        }
    }
    if(it1==categories.end()){
        throw CategoryNotFound();
    }
    categories.erase(it1);

            for(vector<book*>::iterator it=books.begin();it!=books.end();){
                if((*it)->getcategory()==category){
                    string ISBN=(*it)->getISBN();
                    for(int i=0;i<users.size();i++){
                        if(typeid(*users[i])== typeid(loaner)){
                            dynamic_cast<loaner*>(users[i])->remove_book_from_loaners_loans_and_reservations(ISBN);
                        }
                    }
                    delete *it;
                    it=books.erase(it);
                }
                else{
                    ++it;
                }
            }
            std::cout<<"Category removed successfully!"<<std::endl<<std::endl;
}

 void library::setMaxLoans(int numLoans) {
     string fileName="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/MAX_LOANS.txt";
     ofstream file_out(fileName); // Open the CSV file
     if (!file_out) {
         throw CanNotOpenFile();
     }
    file_out<<numLoans;

     library::MaxLoans=numLoans;
}

void library::Loan(const string& id,const string &argument) {
    loaner* current=nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            current = dynamic_cast<loaner *>(users[i]);
            assert(current);
            break;
        }
    }
    book* the_book=nullptr;
    for(int i=0;i<books.size();i++){
        if(books[i]->getISBN()==argument || books[i]->getName()==argument){
            the_book=books[i];
            break;
        }
    }
    if(!the_book){
        throw BookNotFound();
    }
    if(the_book->getQuantity()>0 && current->getTotalLoans()<MaxLoans){
        int end_day;
        int end_month;
        int end_year;
        std::cout<<"Max duration for the  loan:"<<the_book->getDuration()<<std::endl;
        std::cout<<"Please enter date to end the loan:"<<std::endl;
        std::cout<<"Day:"<<std::endl;
        std::cin>>end_day;
        std::cout<<"Month:"<<std::endl;
        std::cin>>end_month;
        std::cout<<"Year:"<<std::endl;
        std::cin>>end_year;
        if(days_from_2000(end_day,end_month,end_year)- days_from_2000(today.day,today.month,today.year)>the_book->getDuration()){
            throw TooLongDuration();
        }
        if(days_from_2000(end_day,end_month,end_year)< days_from_2000(today.day,today.month,today.year)){
            throw InvalidDate();
        }
        current->add_to_loans(the_book->getISBN(),today.day,today.month,today.year,end_day,end_month,end_year);
        the_book->decQuantity();
    }
    else{
        current->add_to_reservations(the_book->getISBN(),today.day,today.month,today.year);
        if(the_book->getQuantity()==0) {
            throw BookOutOfStock();
        }
        if(current->getTotalLoans()>=MaxLoans){
            throw MaxLoansExceeded();
        }
    }
}

void library::ReturnBook(const string& id, const string &argument) {
    book* the_book=nullptr;
    for(int i=0;i<books.size();i++){
        if(books[i]->getISBN()==argument || books[i]->getName()==argument){
            the_book=books[i];
            break;
        }
    }
    if(!the_book){
        throw BookNotFound();
    }
    for(int i=0;i<users.size();i++){
        if(users[i]->getId()==id){
            loaner* theLoaner=dynamic_cast<loaner*>(users[i]);
            theLoaner->finish_loan(the_book->getISBN());
            break;
        }
    }


    for(int i=0;i<books.size();i++){
        if(books[i]->getISBN()==the_book->getISBN()){
            books[i]->incQuantity();
        }
    }

}

void library::ReserveSecretly(const string& id) {
    int num;
    std::cout<<"For sending an encoded book ISBN,Please calculate secretly: x^"<<this->encoding.return_e()<<"(mod"<<this->encoding.return_n()<<
    ") , where x is the first 3 digits of your book's ISBN"<<std::endl;
    std::cout<<"the value you got: "<<std::endl;
    std::cin>>num;
    num=this->encoding.RSA_D(num);

    // Create a stringstream to format the result as a string
    std::stringstream ss;
    ss << num ;

    string ISBN=ss.str()+"0000000000";
    loaner* current=nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            current = dynamic_cast<loaner *>(users[i]);
            assert(current);
            break;
        }
    }
    book* the_book=nullptr;
    for(int i=0;i<books.size();i++){
        if(books[i]->getISBN()==ISBN){
            the_book=books[i];
            break;
        }
    }
    if(!the_book){
        throw BookNotFound();
    }

    current->add_to_reservations(the_book->getISBN(),today.day,today.month,today.year);

    std::cout<<"Your book reserved succesfully! "<<std::endl;

}


void library::CancelReservation(const string& id,const string &argument) {
    book* the_book=nullptr;
    for(int i=0;i<books.size();i++){
        if(books[i]->getISBN()==argument || books[i]->getName()==argument){
            the_book=books[i];
            break;
        }
    }
    if(!the_book){
        throw BookNotFound();
    }
    for(int i=0;i<users.size();i++){
        if(users[i]->getId()==id){
            loaner* theLoaner=dynamic_cast<loaner*>(users[i]);
            theLoaner->cancel_reservation(the_book->getISBN());
            break;
        }
    }
}

void library::PrintLoans(const string& id) {
    loaner* current=nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            current = dynamic_cast<loaner *>(users[i]);
            assert(current);
            break;
        }
    }
    current->printLoans();
}

void library::PrintReservations(const string& id) {
    loaner* current=nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            current = dynamic_cast<loaner *>(users[i]);
            assert(current);
            break;
        }
    }
    current->printReservations();
}

void library::PrintHistory(const string& id) {
    loaner* current=nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getId() == id) {
            current = dynamic_cast<loaner *>(users[i]);
            assert(current);
            break;
        }
    }
    current->printLoanHistory();
}

int library::getmaxloans() {
    string fileName="C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/MAX_LOANS.txt";
    ifstream file_in(fileName); // Open the CSV file
    if (!file_in) {
        std::cerr << "Error: Could not open file - " << fileName << std::endl;
        return -1;
    }
    int numloans;
    file_in>>numloans;

    return numloans;
}

void library::Restore_Password() {
    string password;
    int num;
    std::cout<<"To restore your password ,Please calculate secretly: x^"<<this->encoding.return_e()<<"(mod"<<this->encoding.return_n()<<
             ") , where x is your id"<<std::endl;
    std::cout<<"the value you got: "<<std::endl;
    std::cin>>num;
    num=this->encoding.RSA_D(num);

    // Create a stringstream to format the result as a string
    std::stringstream ss;
    ss << num ;
    for(int i=0;i<users.size();i++){
        if(users[i]->getId()==ss.str()){
            password= users[i]->getPassword();
        }
    }
    std::cout<<"Your password is: "<<password<<std::endl<<std::endl;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int* get_current_date() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&t);

    static int today[3];  // static to ensure the array persists after the function ends

    today[0] = localTime->tm_mday;     // Day
    today[1] = localTime->tm_mon + 1;  // Month (tm_mon is 0-based, so add 1)
    today[2] = localTime->tm_year + 1900; // Year (tm_year is the number of years since 1900)

    return today;
}



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

void deleteFilesOfLoaner(const string& id) {
    string loaner_id = id;
    string loaner_file = loaner_id + "_loanHistory.csv";
    string fileName_historys =
            "C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/" +
            loaner_file;
    string fileName_loans =
            "C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/"
            + loaner_id + "_loans.csv";
    string fileName_reservations =
            "C:/Users/ofekz/OneDrive - Technion/Desktop/Technion/Clion_new_projects/old/C++ Library Project/Library_Data/Library_Directory/"
            + loaner_id + "_reservations.csv";
    if (!std::remove(fileName_historys.c_str()) == 0) {  // Convert std::string to C-style string
        throw CanNotDeleteFiles();
    }
    if (!std::remove(fileName_loans.c_str()) == 0) {  // Convert std::string to C-style string
        throw CanNotDeleteFiles();
    }
    if (!std::remove(fileName_reservations.c_str()) == 0) {  // Convert std::string to C-style string
        throw CanNotDeleteFiles();
    }
}