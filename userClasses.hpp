#include <iostream>
#include <vector>
#include <cstdlib>
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

    void setName(string n) {
        name = n;
    }
    void setContact(string c) {
        contactNum = c;
    }

    virtual void borrowBook(Book* b1) {}
    virtual void returnBook(Book* b1) {}
    virtual void editUserInfo(User* u1) {}
    virtual void setNewFine(float amt) {}
    virtual bool addNewBook(Book b1) {}
    virtual bool removeBook(Book b1) {}
};

class PremiumUser: public User {
    protected:
    const int maxBooks = 10;
    int currentBooksBorrowed;
    vector<Book*> borrowedBooks; 
    const float finePer15Days = 5.0;
    float totalFines;

    public:
    PremiumUser() : User(), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    PremiumUser(string userID, string name, string contactNum) : User(userID, name, contactNum), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    void setNewFine(float amt) override {
        totalFines = totalFines - amt;
    }

    void borrowBook(Book* b1) override {
        if (currentBooksBorrowed == maxBooks) {
            cout << "max borrowing limit reached. return a book to borrow a new one" << endl;
            return;
        }
        bool flag = b1->borrowBook();
        if (flag == true) {
            borrowedBooks.push_back(b1);
            currentBooksBorrowed++;
       }
    }

    void returnBook(Book* b1) override {
        int index = -1;
        for (int i = 0; i<currentBooksBorrowed; i++) {
            if (borrowedBooks[i]->bookID == b1->bookID) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "book " << b1->bookID << " not borrowed by user " << userID << endl;
            return;
        }
        bool flag = b1->returnBook();
        if (flag) {
            int daysOverdue = b1->getDaysOverdue();
            if (daysOverdue >= 15) {
                float fine = (daysOverdue/15) * finePer15Days;
                totalFines += fine;
            }
        }
        borrowedBooks.erase(borrowedBooks.begin() + index);
        currentBooksBorrowed--;
    }

    void editUserInfo(User* u1) override {
        cout << "User cant edit users info" << endl;
    }

    bool addNewBook(Book b1) override {
        cout << "User cannot add new book"<< endl;
        return false;
    }

    bool removeBook(Book b1) override {
        cout << "user cannot remove book" << endl;
        return false;
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

    void setNewFine(float amt) override {
        totalFines = totalFines - amt;
    }

    void borrowBook(Book* b1) override {
        if (currentBooksBorrowed == maxBooks) {
            cout << "max borrowing limit reached. return a book to borrow a new one" << endl;
            return;
        }
        bool flag = b1->borrowBook();
        if (flag == true) {
            borrowedBooks.push_back(b1);
            currentBooksBorrowed++;
       }
    }

    void returnBook(Book* b1) override {
        int index = -1;
        for (int i = 0; i<currentBooksBorrowed; i++) {
            if (borrowedBooks[i]->bookID == b1->bookID) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "book " << b1->bookID << " not borrowed by user " << userID << endl;
            return;
        }
        bool flag = b1->returnBook();
        if (flag) {
            int daysOverdue = b1->getDaysOverdue();
            if (daysOverdue >= 15) {
                float fine = daysOverdue * finePerDay;
                totalFines += fine;
            }
        }
        borrowedBooks.erase(borrowedBooks.begin() + index);
        currentBooksBorrowed--;
    }

    void editUserInfo(User* u1) {
        cout << "User cant edit users info" << endl;
    }

    bool addNewBook(Book b1) override {
        cout << "User cannot add new book"<< endl;
        return false;
    }

    bool removeBook(Book b1) override {
        cout << "user cannot remove book" << endl;
        return false;
    }
};

class Librarian : public User {
    protected:
    float monthlySalary;

    public:
    Librarian() : User(), monthlySalary(0.0) {}

    Librarian(string userID, string name, string contactNum, float monthlySalary) : User(userID, name, contactNum), monthlySalary(monthlySalary) {}

    void borrowBook(Book* b1) override {
        cout << "librarian cant borrow/return books" << endl;
    }

    void returnBook(Book* b1) override {
        cout << "librarian cant borrow/return books" << endl;
    }

    void setNewFine(float amt) override {}

    bool addNewBook(Book b1) {
        cout << "Librarian " << userID << " attempting to add book" << endl;
        return true;
    }

    bool removeBook(Book b1) {
        cout << "Librarian " << userID << " attempting to add book" << endl;
        return true;
    }

    // system class mei for user* object, call this function, if it returns true add book else user cannot add book

    void editUserInfo(User* u1) override {
        int choice;
        cout << "Editing user info: " << endl;
        cout << "1. name\n2. contact number\n3. pay user fine\n4. exit" << endl;
        cin >> choice;

        switch(choice) {
            case 1:{
                string newName;
                cout << "enter new name: ";
                getline(cin, newName);
                u1->setName(newName);
                break;
            }

            case 2:{
                string newContact;
                cout << "enter new contact: ";
                getline(cin, newContact);
                u1->setContact(newContact);
                break;
            }

            case 3:{
                float amountPaid;
                cout << "enter fine paid by user: ";
                cin >> amountPaid;
                u1->setNewFine(amountPaid);
                break;
            }

            case 4:
            cout << "exiting edit user info " << endl;
            exit(0);
            break;
        }
    }
};