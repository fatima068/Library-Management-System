#include <iostream>
#include <vector>
using namespace std;
#include "bookClass.hpp"

class User {
    protected:
    const string userID;
    string name;
    
};

// premium has to pay fine only if book is a month late, normal user has to pay per day fine

class PremiumUser: public User {
    protected:
    vector<Book*> borrowedBooks; // can borrow unlimited number of books
    const float finePerMonth;
};

class NormalUser: public User {
    protected:
    Book* borrowedBooks[5] = {nullptr}; // reserved space of 5 books max
    const float finePerDay;
};