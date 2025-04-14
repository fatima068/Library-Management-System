#include <iostream>
#include <vector>
using namespace std;
// #include "bookClass.hpp"

class User {
    protected:
    const string userID;
    string name;
    string contactNum;

    public:
    User() : userID(""), name(""), contactNum("") {}

    User(string userID, string name, string contactNum) : userID(userID), name(name), contactNum(contactNum) {}

    virtual void borrowBook(Book* b1) {}
    virtual void returnBook() {}
};

class PremiumUser: public User {
    protected:
    const int maxBooks = 7;
    int currentBooksBorrowed;
    vector<Book*> borrowedBooks; 
    const float finePer15Days = 5.0;
    float totalFines;

    public:
    PremiumUser() : User(), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    PremiumUser(string userID, string name, string contactNum) : User(userID, name, contactNum), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    void borrowBook(Book* b1) override {

    }

    void returnBook() override {

    }
};

class NormalUser: public User {
    protected:
    const int maxBooks = 3;
    vector<Book*> borrowedBooks; 
    int currentBooksBorrowed;
    const float finePerDay = 0.5;
    float totalFines;

    public:
    NormalUser() : User(), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    NormalUser(string userID, string name, string contactNum) : User(userID, name, contactNum), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    void borrowBook(Book* b1) override {

    }

    void returnBook() override {

    }
};

class Librarian : public User {
    protected:

    public:
    Librarian() : User() {}

    void borrowBook(Book* b1) override {
        cout << "librarian cant borrow/return books" << endl;
    }

    void returnBook() override {
        cout << "librarian cant borrow/return books" << endl;
    }
};