#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "allClasses.hpp"
using namespace std;

class System {
    private:
    vector<User*> allUsers;
    vector<Book> allBooks;

    public:
    void searchBookName() {
        string nameToSearch;
        cout << "enter book name to search: ";
        getline(cin, nameToSearch);
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].title == nameToSearch) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }

    void searchAuthorName() {
        string authorToSearch;
        cout << "enter author to search: ";
        getline(cin, authorToSearch);
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].author == authorToSearch) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }

    void searchBookId() {
        string bookIDtoSearch;
        cout << "enter book id to search: "; 
        getline(cin, bookIDtoSearch);
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].bookID == bookIDtoSearch) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }
    
    void searchUserName() {
        string nameToSearch;
        cout << "enter user name to search: ";
        getline(cin, nameToSearch);
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->name == nameToSearch) {
                cout << allUsers[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl;
        } 
    }
    
    void searchUserId() {
        string idToSearch;
        cout << "enter user name to search: ";
        getline(cin, idToSearch);
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->userID == idToSearch) {
                cout << allUsers[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl;
        } 
    }

    User* findUser(const string& userID) {
        for (User* user : allUsers) {
            if (user->userID == userID) {
                return user;
            }
        }
        return nullptr;
    }

    void loadBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }
    
        string bookData[10]; 
        
        while (getline(allBooksFile, bookData[0])) {  // Read bookID
            // Read the remaining 7 fields
            for (int i = 1; i < 10; i++) {
                if (!getline(allBooksFile, bookData[i])) {
                    cerr << "Incomplete book record" << endl;
                    return;
                }
            }
    
            bool borrow = (bookData[5] == "true"); // convert string to bool
            int dd = stoi(bookData[6]);
            int mm = stoi(bookData[7]); 
            int yy = stoi(bookData[8]); 
            
            int timesRenewed = stoi(bookData[9]);  // convert string to int
    
            // Create and store the book
            Book temp(bookData[0], bookData[1], bookData[2], bookData[3], bookData[4], borrow, dd, mm, yy, timesRenewed);
            allBooks.push_back(temp);
        }
        
        allBooksFile.close();
        cout << "Loaded " << allBooks.size() << " books" << endl;
    }

    void saveBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }

        allBooksFile.close();
    }

    void displayAllBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            cout << allBooks[i];
        }
    }

    void displayBorrowedBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].isBorrowed)
                cout << allBooks[i];
        }
    }

    void displayAvailBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            if (!allBooks[i].isBorrowed)
                cout << allBooks[i];
        }
    }

    void LibrarianMenu() {
        int choice = -1;
        while(choice != 8) {
            cout << "1. search book\n2. search user\n3. delete a user account\n4. view book list\n5. add new book to library\n6. remove a book\n 7. edit user info\n8. exit\nenter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    int choice; 
                    cout << "1. by book name\n2. by author name\n3. by book id\nenter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            searchBookName();
                            break;
                        }
                        case 2: {
                            searchAuthorName();
                            break;
                        } 
                        case 3: { 
                            searchBookId();
                            break;
                        }
                        default:
                            cout << "wrong choice " << endl; 
                            break;
                    }
                    break;
                }

                case 2: {
                    int choice; 
                    cout << "1. by user name\n2. by book id\nenter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            searchUserName(); 
                            break;
                        }

                        case 2: {
                            searchUserId();
                            break;
                        }

                        default:
                            cout << "wrong choice" << endl; 
                            break;
                    }
                    break;
                }

                case 3: {
                    break;
                }

                case 4: {
                    int choice; 
                    cout << "1. view all books\n2. view borrowed books\n3. view available books\n4";
                    cin >> choice; 
                    switch (choice) {
                        case 1: {
                            displayAllBooks();
                            break;
                        }
                        case 2: {
                            displayBorrowedBooks();
                            break;
                        }
                        case 3: {
                            displayAvailableBooks(); 
                            break;
                        }

                        default:
                            cout << "invalid choice " << endl; 
                            break;
                    }
                    break;
                }

                case 5: {
                    break;
                }

                case 6: {
                    break;
                }

                case 7: {
                    break;
                }

                case 8: {
                    cout << "exiting menu..." << endl; // c later if program can be exited instead of break
                    break;
                }
            }
        }
    }

    void displayAllBooks() {}
    void displayBorrowedBooks() {}
    void displayAvailableBooks() {}

    void userMenu() {

    }

    ~System() {
        for (User* user : allUsers) {
            delete user;
        }
        
    }
};

// search user by id
// search book by name (done)
// search book by author (done)
// search book by genre 
// search book by id 
// create a new user 
// delete user from system 
// view all available books 
// view all borrowed books
// renew a borrowed book
// session management and axxess control seekhn hai 

#endif