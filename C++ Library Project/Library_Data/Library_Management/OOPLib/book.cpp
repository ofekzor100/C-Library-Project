//
// Created by ofekz on 3/11/2025.
//

#include "book.h"

book::book(string ISBN, string name, string author, int year, string category, int quantity, int duration):ISBN(ISBN),
                                                                                                           name(name),author(author),year(year),category(category),quantity(quantity),duration(duration) {

}

void book::setName(string name) {
    this->name=name;
}

void book::setAuthor(string author) {
    this->author=author;
}

void book::setYear(int year) {
    this->year=year;
}

void book::setCategory(string category) {
    this->category=category;
}

void book::setQuantity(int quantity) {
    this->quantity=quantity;
}

void book::setDuration(int duration) {
    this->duration=duration;
}

string book::getISBN() {
    return this->ISBN;
}

void book::incQuantity() {
    this->quantity++;
}

string book::getName() {
    return this->name;
}

string book::getAuthor() {
    return this->author;
}

int book::getYear() {
    return this->year;
}

string book::getcategory() {
    return this->category;
}

int book::getQuantity() {
    return this->quantity;
}

int book::getDuration() {
    return this->duration;
}



void book::decQuantity() {
    this->quantity--;
}
