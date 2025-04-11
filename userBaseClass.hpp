#include <iostream>
#include <string>
#include <vector>
#include "bookClass.hpp"
using namespace std;

class User {
    private:
    const string userID;

    protected:
    string userName;
    int borrowedBookCount;
    vector<Book> borrowedBooks; // 3 for normal user, 10 for premium

    public:
    User(string id) : userID(id), userName(""), borrowedBookCount(0) {}

    User(string id, string name) : userID(id), userName(name), borrowedBookCount(0) {} // when user is registered, they havent borrowed any books initially. Usske liye baad mei functions call honge 

    string getUserID() const {
        return userID;
    }

    void borrowBook(vector<Book> book) {
        // check if book is available
        // check if user has reached max limit
        // if yes, print max limit reached
        // else, add book to borrowedBooks vector
        // increment borrowedBookCount
        // toggle availability of book
        // how to check usertype?
        

    }

    void returnBook(vector<Book> book) {
        borrowedBooks.pop_back();
        borrowedBookCount--;
    }

    void displayBorrowedBooks() {
        cout << "Books borrowed by " << userName << " are: " << endl;
        for (int i = 0; i < borrowedBooks.size(); i++) {
            cout << borrowedBooks[i];
        }
    }
};