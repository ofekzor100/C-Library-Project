cmake_minimum_required(VERSION 3.20)
project(OOPLib)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../../../Library_CLI")



add_library(OOPLib library.cpp user.cpp librarian.cpp loaner.cpp book.h book.cpp
         reservation.cpp  loan.cpp loan_history.cpp RSA.cpp Exceptions.h)


add_executable(Main Main.cpp)
target_link_libraries(Main OOPLib)
