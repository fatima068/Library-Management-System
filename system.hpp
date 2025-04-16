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
    public:
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
                    ofstream allBooksFile("textFiles/allBooks.txt");
                    if (!allBooksFile) {
                        cerr << "error in opening all books.txt file" << endl;
                    }
                    switch (choice) {
                        case 1: {
                            string nameToSearch;
                            
                        }
                    }
                    allBooksFile.close();
                    break;
                }

                case 2: {
                    ofstream allUsersFile("textFiles/allBooks.txt");
                    if (!allUsersFile) {
                        cerr << "error in opening all users.txt file" << endl;
                    }
                    switch (choice) {
                        case 1: {
                            string userIDtoSearch;
                            
                        }
                    }
                    allUsersFile.close();
                    break;
                }

                case 3: {
                    break;
                }

                case 4: {
                    int choice; 
                    cout << "1. view all books\n2. view borrowed books\n3. view available books\n4";
                    cin >> choice; 
                    ofstream allBooksFile("textFiles/allBooks.txt");
                    if (!allBooksFile) {
                        cerr << "error in opening all books.txt file" << endl;
                    }
                    switch (choice) {
                        case 1: {
                            
                            
                        }
                    }
                    allBooksFile.close();
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