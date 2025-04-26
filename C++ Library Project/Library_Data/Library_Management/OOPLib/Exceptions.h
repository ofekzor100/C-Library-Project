//
// Created by ofekz on 3/21/2025.
//

#ifndef MAIN_CPP_EXCEPTIONS_H
#define MAIN_CPP_EXCEPTIONS_H
class Exception : public std::exception{};
class InvalidCommand : public Exception {};
class WrongPassword : public Exception {};
class UserNotFound : public Exception {};
class CanNotOpenFile : public Exception {};
class BookNotFound : public Exception {};
class NoMoreBooks : public Exception {};
class SearchNotFound : public Exception {};
class NotValidId : public Exception {};
class IdInUse : public Exception {};
class InvalidISBN : public Exception {};
class ISBNInUse : public Exception {};
class InvalidYear : public Exception {};
class CategoryNotFound : public Exception {};
class InvalidQuantity : public Exception {};
class InvalidDuration : public Exception {};
class DontRemoveOtherLibrarian : public Exception {};
class ClientNotFound : public Exception {};
class TooLongDuration : public Exception {};
class InvalidDate : public Exception {};
class BookOutOfStock : public Exception {};
class MaxLoansExceeded : public Exception {};
class CanNotDeleteFiles : public Exception {};
class CanNotCreateFile : public Exception {};
class BookNotLoaned : public Exception {};
class BookNotReserved : public Exception {};
class InvalidCategory : public Exception {};
#endif //MAIN_CPP_EXCEPTIONS_H
