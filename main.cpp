#include <iostream>
#include "system.hpp"
#include "login.hpp"
using namespace std;

//oke so abhi we havent done this but
//first we'll make an object of loginsystem, and then we ask for an id from user
//we pass that id into login() and get a true or false of if valid, haina
//so then if false we'll be like bruh give a correct password
//if true to we have to see what type of user has logined
//to i finking, we make some function in system class, where we pass the id and we find id from the array and store everything from there to the pointer logined user (pssss i made a function in system, i.e. logAUser(string id) )
//this will make our life very very easier pleaseeeeee

int main() {
    LoginSystem loginSystem; 
    System librarySystem;

    // Load initial data
    librarySystem.loadBooks();
    
    // Test login
    string userID;
    cout << "Enter user ID: ";
    getline(cin, userID);
    
    if (loginSystem.login(userID)) {
        librarySystem.logAUser(userID);
        
        // Determine user type and show appropriate menu
        char userType = loginSystem.getUserType();
        
        if (userType == 'L') { // Librarian
            cout << "\n=== LIBRARIAN MENU ===" << endl;
            librarySystem.LibrarianMenu();
        } 
        else { // Normal or Premium User
            cout << "\n=== USER MENU ===" << endl;
            librarySystem.userMenu();
        }
    } else {
        cout << "Login failed. Exiting..." << endl;
    }

    librarySystem.saveBooks();
}