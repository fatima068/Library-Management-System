#include <iostream>
#include "system.hpp"
using namespace std;

int main() { 
    System librarySystem;
    int choice;
    string userID;
    cout << "1. LOGIN\n2. SIGN UP" <<  endl;
    cin >> choice ;
    switch (choice) {
        case 1:
        cin.ignore();
        cout << "Enter your User ID: ";
        getline(cin, userID);
        if (librarySystem.loginUser(userID)) {
            char userType = librarySystem.getCurrentUserType();
            librarySystem.logAUser(userID);
            librarySystem.loadBooks();
            
            if (userType == 'P') {
                librarySystem.loadPremiumUsers();
                librarySystem.userMenu();
            } 
            else if (userType == 'N') {
                librarySystem.loadNormalUsers();
                librarySystem.userMenu();
            }
            else if (userType == 'L') {
                librarySystem.loadLibrarian();
                librarySystem.LibrarianMenu();
            }
            
        } else {
            cout << "Login failed. Exiting..." << endl;
        }
        break;

        case 2:
            librarySystem.signUp();
            break;    
    }
}