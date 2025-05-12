#include <iostream>
#include <exception>
#include "system.hpp"
using namespace std;

class invalidLoginInputException : public exception {
    public:
    const char* what() const noexcept override {
        return "error: enter 1 or 2!";
    }
};

int main() { 
    System librarySystem;
    int choice;
    string userID;
    try
    {
        cout << "1. LOGIN\t2. SIGN UP" <<  endl << "your choice: ";
        cin >> choice ; 
        if (!(choice == 1 || choice == 2)) { throw invalidLoginInputException(); }
    }
    catch(const invalidLoginInputException& e)
    {
        cerr << e.what() << endl;;
    }
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
    }
}