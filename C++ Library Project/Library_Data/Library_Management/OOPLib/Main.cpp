//
// Created by ofekz on 3/10/2025.
//

//
// Created by ofekz on 3/10/2025.
//

#include <iostream>
#include <string>
#include "library.h"
using std::string;


void user_verification(string& id,string& password, library& new_library,bool& is_librarian);
void launch_the_app(const string& id,library& new_library,const bool& is_librarian);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    try {

        std::cout << "Welcome to The Library application!" << std::endl;
        library new_library;
        bool is_librarian = false;
        string id;
        string password;
        user_verification(id, password, new_library, is_librarian);
        launch_the_app(id, new_library, is_librarian);

        return 0;
    }

    catch(CanNotOpenFile& e){
        std::cerr << "Error: Could not open file  " <<std::endl;
        std::cout << "---------------------------------------"<<std::endl<<std::endl;
    }
    catch(CanNotDeleteFiles& e){
        std::cerr << "Error: Could not delete file (File may not exist or is in use)" << std::endl;
        std::cout << "---------------------------------------"<<std::endl<<std::endl;
    }
    catch(CanNotCreateFile& e){
        std::cerr << "Error: Could not create file - "  << std::endl;
        std::cout << "---------------------------------------"<<std::endl<<std::endl;
    }
    catch(InvalidDate& e){
        std::cout<<"Invalid date!"<<std::endl;
        std::cout << "---------------------------------------"<<std::endl<<std::endl;
    }
    catch(TooLongDuration& e){
        std::cout<<"Loan duration is too long for this book!"<<std::endl;
        std::cout << "---------------------------------------"<<std::endl<<std::endl;
    }


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void user_verification(string& id,string& password,library& new_library, bool& is_librarian){
    while(1) {
        try {
            string forgot;
            std::cout << "Forgot password? Enter Y to securely restore your password, or enter any other string to  log in. " << std::endl;
            std::cin>>forgot;
            if(forgot=="Y"){
                new_library.Restore_Password();
            }
            else{
                std::cin.clear();
            }
            std::cout << "Please enter ID:" << std::endl;
            std::cin >> id;
            std::cout << "Please enter password:" << std::endl;
            std::cin >> password;

            if (password == "OOPLib") {
                string name;
                name = new_library.create_librarian(id);
                is_librarian = true;
                std::cout << "Hello " << name << " !" << std::endl;
                break;
            }
            new_library.user_verify(is_librarian, id, password);
            break;

        }
        catch(UserNotFound& e){
            std::cout << "User not found" << std::endl;
        }
        catch(WrongPassword& e){
            std::cout << "Wrong password!" << std::endl;
        }

    }
}




void launch_the_app(const string& id,library& new_library,const bool& is_librarian){

    std::cout << "Here are some actions you can take: " << std::endl;
    std::cout << "---------------------------------------"<<std::endl;
    std::cout << "Print <ISBN>" << std::endl;
    std::cout << "PrintBooks <category>" << std::endl;
    std::cout << "Search <search_text>" << std::endl;
    std::cout << "Update " << std::endl;
    if(is_librarian){
        std::cout << "AddBook" << std::endl;
        std::cout << "UpdateBook" << std::endl;
        std::cout << "RmBook <ISBN>" << std::endl;
        std::cout << "AddClient" << std::endl;
        std::cout << "Rmclient <id>" << std::endl;
        std::cout << "AddCategory <category>" << std::endl;
        std::cout << "RmCategory <category>" << std::endl;
        std::cout << "SetMaxLoans <numLoans>" << std::endl;
    }
    else{
        std::cout << "Loan <ISBN>" << std::endl;
        std::cout << "Loan <name>" << std::endl;
        std::cout << "Return <ISBN>" << std::endl;
        std::cout << "Return <name>" << std::endl;
        std::cout << "ReserveSecretly" << std::endl;
        std::cout << "Cancel <ISBN>" << std::endl;
        std::cout << "Cancel <name>" << std::endl;
        std::cout << "PrintLoans" << std::endl;
        std::cout << "PrintReservations" << std::endl;
        std::cout << "PrintHistory" << std::endl;
    }
    std::cout << "Exit" << std::endl<<std::endl;
    while (1) {
        try {


            std::cin.clear();
            string command, argument;
            std::cout << "Enter command: ";
            std::cin >> command;
            std::getline(std::cin, argument);
            if (!argument.empty() && argument[0] == ' ') {
                argument.erase(0, 1);
            }

            if (command == "Print") {
                new_library.printBook(argument);
                continue;
            }
            if (command == "PrintBooks") {
                new_library.printBooksByCategory(argument);
                continue;
            }
            if (command == "Search") {
                new_library.search(id, argument);
                continue;
            }
            if (command == "Update") {
                new_library.update(id);
                continue;
            }
            if (command == "Exit") {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            if (is_librarian) {
                if (command == "AddBook") {
                    new_library.addBook();
                    continue;
                }
                if (command == "UpdateBook") {
                    new_library.updateBook();
                    continue;
                }
                if (command == "RmBook") {
                    new_library.removeBook(argument);
                    continue;
                }
                if (command == "AddClient") {
                    new_library.addClient();
                    continue;
                }
                if (command == "RmClient") {
                    new_library.removeClient(argument);
                    continue;
                }
                if (command == "AddCategory") {
                    new_library.addCategory(argument);
                    continue;
                }
                if (command == "RmCategory") {
                    new_library.removeCategory(argument);
                    continue;
                }
                if (command == "setMaxLoans") {
                    library::setMaxLoans(std::stoi(argument));
                    continue;
                }

            } else {
                if (command == "Loan") {
                    new_library.Loan(id, argument);
                    continue;
                }
                if (command == "Return") {
                    new_library.ReturnBook(id, argument);
                    continue;
                }
                if (command == "ReserveSecretly") {
                    new_library.ReserveSecretly(id);
                    continue;
                }
                if (command == "Cancel") {
                    new_library.CancelReservation(id, argument);
                    continue;
                }
                if (command == "PrintLoans") {
                    new_library.PrintLoans(id);
                    continue;
                }
                if (command == "PrintReservations") {
                    new_library.PrintReservations(id);
                    continue;
                }
                if (command == "PrintHistory") {
                    new_library.PrintHistory(id);
                    continue;
                }
            }

            throw InvalidCommand();

        }
        catch(InvalidCommand& e){
            std::cout << "Invalid command!" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(CanNotOpenFile& e){
            std::cerr << "Error: Could not open file  " <<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(BookNotFound& e){
            std::cout << "Book not found!"<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(NoMoreBooks& e){
            std::cout << "  There are no more books in that category" << std::endl;
            std::cout << "---------------------------------------" << std::endl << std::endl;
        }
        catch(SearchNotFound& e){
            std::cout << " Not found any matches!"<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(NotValidId& e){
            std::cout << "Please enter a valid id !" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(IdInUse& e){
            std::cout<<"Another user has this ID. ID MUST BE UNIQUE!"<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(InvalidISBN& e){
            std::cout << "Please enter a valid ISBN !" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(ISBNInUse& e){
            std::cout << " The library already has a book with this ISBN. Please use other ISBN. "  <<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(InvalidYear& e){
            std::cout << "Please enter a valid year !" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(CategoryNotFound& e){
            std::cout << " Category not found! "  <<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(InvalidQuantity& e){
            std::cout << "Please enter a valid quantity !" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(InvalidDuration& e){
            std::cout << "Please enter a valid duration !" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(DontRemoveOtherLibrarian& e){
            std::cout << "Please don't try to remove other librarian!" << std::endl<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(ClientNotFound& e){
            std::cout << "Client not found !" << std::endl<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(TooLongDuration& e){
            std::cout<<"Loan duration is too long for this book!"<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(InvalidDate& e){
            std::cout<<"Invalid date!"<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(BookOutOfStock& e){
            std::cout << "Book is out of stock, added to reservations." << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(MaxLoansExceeded& e){
            std::cout << "max loans exceeded" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(CanNotDeleteFiles& e){
            std::cerr << "Error: Could not delete file (File may not exist or is in use)" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(CanNotCreateFile& e){
            std::cerr << "Error: Could not create file - "  << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(BookNotLoaned& e){
            std::cout << "Book is not loaned" << std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(BookNotReserved& e){
            std::cout<<"the book is not reserved"<<std::endl<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }
        catch(InvalidCategory& e){
            std::cout<<"PLease enter  a valid category!"<<std::endl<<std::endl;
            std::cout << "---------------------------------------"<<std::endl<<std::endl;
        }

    }
}

