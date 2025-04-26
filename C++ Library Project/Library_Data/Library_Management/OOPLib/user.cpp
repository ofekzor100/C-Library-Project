//
// Created by ofekz on 3/10/2025.
//

#include "user.h"

user::user(string id, string name, string password):id(id),name(name),password(password) {}

string user::getId() const {
    return this->id;
}

string user::getName() const {
    return this->name;
}

string user::getPassword() const {
    return this->password;
}

void user::setId(const string& id) {
    this->id=id;
}

void user::setName(const string& name) {
    this->name=name;
}

void user::setPassword(const string& password) {
    this->password=password;
}


