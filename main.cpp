#include <iostream>
#include "system.hpp"
using namespace std;

//oke so abhi we havent done this but
//first we'll make an object of loginsystem, and then we ask for an id from user
//we pass that id into login() and get a true or false of if valid, haina
//so then if false we'll be like bruh give a correct password
//if true to we have to see what type of user has logined
//to i finking, we make some function in system class, where we pass the id and we find id from the array and store everything from there to the pointer logined user (pssss i made a function in system, i.e. logAUser(string id) )
//this will make our life very very easier pleaseeeeeee

int main() {
    //LoginSystem obj; 
    System librarySystem;
    
    // Load initial data
    librarySystem.loadBooks();
    // librarySystem.loadUsers(); // Uncomment when implemented
    
    // Test book search functionalities
    cout << "=== Testing Book Search ===" << endl;
    librarySystem.searchBookName();
    librarySystem.searchAuthorName();
    librarySystem.searchBookId();
    
    // Test user search functionalities
    cout << "\n=== Testing User Search ===" << endl;
    librarySystem.searchUserName();
    librarySystem.searchUserId();
    
    // Test librarian menu
    cout << "\n=== Testing Librarian Menu ===" << endl;
    librarySystem.LibrarianMenu();
    
    // Test user menu
    cout << "\n=== Testing User Menu ===" << endl;
    librarySystem.userMenu();
    
    // Save data before exiting
    // librarySystem.saveUsers(); // Uncomment when implemented
    librarySystem.saveBooks();
    
    return 0;
}