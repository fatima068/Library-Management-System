#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <limits>
#include "allClasses.hpp"
using namespace std;

class System {
    private:
    vector<User*> allUsers;
    vector<Book> allBooks;
    User* loginedUser;

    public:
    void logAUser(string id) { // will this work lets hope it does lmao
        for (int i = 0; i < allUsers.size(); i++) {
            if (id == allUsers[i]->userID) {
                loginedUser = allUsers[i];
            }
        }
    }

    void searchBookName() {
        string nameToSearch;
        cout << "enter book name to search: ";
        
        getline(cin, nameToSearch);
        cout << endl;
        // Trim whitespace from the search input
        // nameToSearch.erase(nameToSearch.find_last_not_of(" \t\n\r\f\v") + 1);
        // nameToSearch.erase(0, nameToSearch.find_first_not_of(" \t\n\r\f\v"));
    
        bool flag = false;
        for (int i = 0; i < allBooks.size(); i++) { 
            if (allBooks[i].title == nameToSearch) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    } 
    
    void searchAuthorName() {
        string authorToSearch;
        cout << "enter author to search: ";
        getline(cin, authorToSearch);
        cout << endl;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].author == authorToSearch) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    }

    void searchBookId() {
        string bookIDtoSearch;
        cout << "enter book id to search: "; 
        getline(cin, bookIDtoSearch);
        cout << endl;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].bookID == bookIDtoSearch) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    }
    
    void searchUserName() {
        string nameToSearch;
        cout << "enter user name to search: ";
        getline(cin, nameToSearch);
        cout << endl;
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->name == nameToSearch) {
                cout << allUsers[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl << endl;
        } 
    }
    
    void searchUserId() {
        string idToSearch;
        cout << "enter user name to search: ";
        getline(cin, idToSearch);
        cout << endl;
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->userID == idToSearch) {
                cout << allUsers[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl << endl;
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
        ofstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }

        for (int i = 0; i < allBooks.size(); i++) {
            allBooks[i].addBookToFile();
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

    void displayAvailableBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            if (!allBooks[i].isBorrowed)
                cout << allBooks[i];
        }
    }

    void displayUserBorrowedBooks() {
        //oke so we make a function for this in users 
        loginedUser->displayBooksBorrowed();
    }

    void borrowBook() { 
        // string id;
        // cout << "enter Book ID of book you want to borrow: ";
        // cin >> id;
        // if (loginedUser->isBookBorrowed(id)) {
        //     cout << "You have already borrowed the Book" << endl;
        //     return;
        // }

        // for (int i = 0; i < allBooks.size(); i++) {
        //     if (id == allBooks[i].bookID) {
        //         allBooks[i].borrowBook();
        //         return;
        //     }
        // }
        // cout << "Book ID doesn't exist" << endl;
    }

    void returnBook() {

    }

    void LibrarianMenu() {
        int choice = -1;
        while(choice != 8) {
            cout << "1. search book\n2. search user\n3. delete a user account\n4. view book list\n5. add new book to library\n6. remove a book\n 7. exit\nenter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: { // search book
                    int choice1; 
                    cout << "1. by book name\n2. by author name\n3. by book id\nenter your choice: ";
                    cin >> choice1;
                    switch (choice1) {
                        case 1: {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // a leftover newline character in the input buffer after using cin >> choice in the menu, which causes getline() to read an empty string immediately afterward.
                            searchBookName();
                            break;
                        }
                        case 2: {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            searchAuthorName();
                            break;
                        } 
                        case 3: { 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            searchBookId();
                            break;
                        }
                        default:
                            cout << "wrong choice " << endl; 
                            break;
                    }
                    break;
                }

                case 2: { // search user
                    int choice2; 
                    cout << "1. by user name\n2. by book id\nenter your choice: ";
                    cin >> choice2;
                    switch (choice2) {
                        case 1: {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            searchUserName(); 
                            break;
                        }

                        case 2: {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            searchUserId();
                            break;
                        }

                        default:
                            cout << "wrong choice" << endl; 
                            break;
                    }
                    break;
                }

                case 3: { // delete user account
                    break;
                }

                case 4: { // view book list
                    int choice3; 
                    cout << "1. view all books\n2. view borrowed books\n3. view available books\nenter your choice: ";
                    cin >> choice3; 
                    switch (choice3) {
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

                case 5: { // add new book to library
                    string id, isbn, title, author, genre;
                    cout << "Enter book details of book to add" << endl;
                    cout << "Book ID: "; // should i first check if its unique ? 
                    getline(cin, id);
                    cout << "ISBN: ";
                    getline(cin, isbn);
                    cout << "Title: ";
                    getline(cin, title);
                    cout << "Author: ";
                    getline(cin, author);
                    cout << "Genre: ";
                    getline(cin, genre);
                    Book b1 = Book(id, isbn, title, author, genre, false, 0, 0, 0);
                    allBooks.push_back(b1);
                    break;
                }

                case 6: { // remove a book
                    string idToRemove;
                    cout << "enter book id of book to remove: ";
                    getline(cin, idToRemove);
                    for (int i = 0; i < allBooks.size(); i++) {
                        if (allBooks[i].bookID == idToRemove) {
                            allBooks.erase(allBooks.begin() + i);
                            cout << "book " << idToRemove << " rempved successfully" << endl;
                            return;
                        }
                        cout << "book not found" << endl;
                    }
                    break;
                }

                case 7: {
                    cout << "exiting menu..." << endl; // maybe give logout option here ? make logout function in login system class
                    break;
                }

                default:
                    cout << "wrong choice" << endl; 
                    break;
            }
        }
    }

    

    void userMenu() {
        int choice = -1;
        while(choice != 7) {
            cout << "1. search book\n2. view book list\n3. borrow book\n4. return book\n5. pay fine\n6. renew book \n7. exit\nenter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: { // search book
                    int choice1; 
                    cout << "1. by book name\n2. by author name\n3. exit\nenter your choice: ";
                    cin >> choice1;
                    switch (choice1) {
                        case 1: {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            searchBookName();
                            break;
                        }
                        case 2: {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            searchAuthorName();
                            break;
                        } 

                        case 3: {
                            cout << "exiting book search menu" << endl;
                            break;
                        }

                        default:
                            cout << "wrong choice " << endl; 
                            break;
                    }
                    break;
            }

            case 2: { // view book list
                    int choice3; 
                    cout << "1. view all books\n2. view borrowed books\n3. view available books\nenter your choice: ";
                    cin >> choice3; 
                    switch (choice3) {
                        case 1: {
                            displayAllBooks();
                            break;
                        }
                        case 2: {
                            // displayUserBorrowedBooks(); // remove this maybe because does user even need to know borrowed books alag se like this ? 
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

            case 3: { //borrow book
                // borrowBook();
                break;
            }

            case 4: { //return book
                
                // something about pointers is confusing. maybe try removing pointers from user class return book function by calling return book for both book and user in system class instead of in user class by passing book as pointer

                // string idToReturn;
                // Book* b1;
                // cout << "enter id of book to return: ";
                // getline(cin, idToReturn);
                // for (int i=0; i<allBooks.size(); i++) {
                //     if (allBooks[i].bookID == idToReturn) {
                //         allBooks[i].returnBook();
                //     }
                // }
                // loginedUser->returnBook(b1);
                break;
            }

            case 5: { //pay fine
                //this can be done yahin pe maybe
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loginedUser->payFine();
                break;
            }

            case 6: { //renew book
                // loginedUser->renewBook()

                // try removing pointers from here as well. 
                // what we can do is edit user to rmeove or include books borrowed by them separately, then search for book id in all books vector and edit that separately over here, no need to make a sepaarte function because function not a part of librarian class.
                break;
            }

            case 7: {
                cout << "exiting menu..." << endl; // c later if program can be exited instead of break
                    break;
                break;
            }

            default:
                cout << "wrong choice" << endl; 
                break;
            }
        }
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