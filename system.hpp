#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "userClasses.hpp"
#include "login.hpp"
#include "bookClass.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class System {
    private:
    vector<User*> allUsers;
    vector<Book> allBooks;

    public:
    void searchBookName() {
        string nameToSearch;
        cout << "enter book name to search: ";
        cin >> nameToSearch;
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
        cin >> authorToSearch;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].title == authorToSearch) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }

    void searchBookId() {
        string is_default_constructible;
        cout << "enter book id to search: ";
        cin >> is_default_constructible;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].title == is_default_constructible) {
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
        cin >> nameToSearch;
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
        cin >> idToSearch;
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

    // Pseudocode for loading users

//         if (type == "Premium") {
//             user = new PremiumUser(id, name, contact);
//         } 
//         else if (type == "Normal") {
//             user = new NormalUser(id, name, contact);
//         }
//         else if (type == "Librarian") {
//             float salary;
//             userFile >> salary;
//             user = new Librarian(id, name, contact, salary);
//         }
        
//         if (user) {
//             allUsers.push_back(user);
//         }
//     }
//     userFile.close();
// }

    // void loadUsers() { // load all users from file to vector 
    //     ifstream allUsersFile("textFiles/allUsers.txt");
    //     if (!allUsersFile) {
    //         cerr << "Error in opening all users file" << endl;
    //         return;
    //     }

    //     allUsersFile.close();
    // }

    // void saveUsers() { // at the end of program, save back to file
    //     ifstream allUsersFile("textFiles/allUsers.txt");
    //     if (!allUsersFile) {
    //         cerr << "Error in opening all users file" << endl;
    //         return;
    //     }

    //     allUsersFile.close();
    // }
    
    void loadBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }

        string line, bookid, isbn, title, author, genre;
        int dd, mm, yy, timesRenewed;
        bool borrow;

        while (getline(allBooksFile, line)) {  
            bookid = line;
                
            getline(allBooksFile, line);  
            isbn = line;
            
            getline(allBooksFile, line);  
            title = line;
            
            getline(allBooksFile, line);  
            author = line;
            
            getline(allBooksFile, line);  
            genre = line;
            
            getline(allBooksFile, line);
            borrow = (line == "true");
            
            getline(allBooksFile, line);

            dd = stoi(line.substr(0, 2));
            mm = stoi(line.substr(2, 2));
            yy = stoi(line.substr(4, 4));
            
            getline(allBooksFile, line);  
            timesRenewed = stoi(line);
            
            Book temp = Book(bookid, isbn, title, author, genre, borrow, dd, mm, yy);
            allBooks.push_back(temp);
        }
        allBooksFile.close();
    }

    void saveBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }

        allBooksFile.close();
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
                            cout << "wrong input dumbass" << endl; // change this pls lmao
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
                            cout << "wrong input dumbass" << endl; // change this pls lmao
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
                            //displayAllBooks();
                            break;
                        }
                        // case 1: {
                        //     //displayBorrowedBooks();
                        //     break;
                        // }
                        // case 1: {
                        //     //displayAvailBooks(); 
                        //     break;
                        // }
                        default:
                            cout << "wrong input dumbass" << endl; // change this pls lmao
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

    void userMenu() {

    }

    ~System() {
        for (User* user : allUsers) {
            delete user;
        }
    }
};

// search user by id
// search book by name 
// search book by author
// search book by genre 
// search book by id 
// create a new user 
// delete user from system 
// view all available books 
// view all borrowed books
// renew a borrowed book
// session management and axxess control seekhn hai 

#endif