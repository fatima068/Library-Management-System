#include <iostream>
#include "system.hpp"
using namespace std;

int main() { 
    System librarySystem;
    int choice;
    string userID;
    cout << "1. LOGIN\t2. SIGN UP" <<  endl << "your choice: ";
    cin >> choice ;
    switch (choice) {
        case 1:
        cin.ignore();
        cout << "Enter your User ID: ";
        getline(cin, userID);
        if (librarySystem.loginUser(userID)) {
            char userType = librarySystem.getCurrentUserType();
            librarySystem.loadBooks();
            
            if (userType == 'P') {
                librarySystem.loadPremiumUsers();
                librarySystem.userMenu(userID);
            }
            else if (userType == 'N') {
                librarySystem.loadNormalUsers();
                librarySystem.userMenu(userID);
            }
            else if (userType == 'L') {
                librarySystem.loadLibrarian();
                librarySystem.LibrarianMenu(userID);
            } 
        } else {
            cout << "Login failed. Exiting..." << endl;
        }
        break;

        case 2:
            librarySystem.signUp();
            break;  

        default:
            cout << "Invalid input. Exiting..." << endl; 
            break;  
    }
}