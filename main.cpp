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
        cin.ignore(); // Clear input buffer
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
                cout << "librarians loadded w out error" << endl;
                librarySystem.LibrarianMenu();
            }
            
        } else {
            cout << "Login failed. Exiting..." << endl;
        }
        break;

        case 2:
            // register a new user here 
            break;
            
    }
    // librarySystem.loadLibrarian();
    // librarySystem.mainMenu();
    // User* u1 = new PremiumUser("P100", "fatima", "0330");
    // User* u2 = new Librarian("L100", "fama", "03322", 50000.0);
    // User* u3 = new NormalUser("N100", "ikrash", "033068");
    return 0;
}

//         case 2:
//             // Sign up functionality to be implemented
//             cout << "Sign up functionality coming soon!" << endl;
//             break;
//         default:
//             cout << "Invalid choice. Exiting..." << endl;
//             break;
//     }

// }

//oke so abhi we havent done this but
//first we'll make an object of loginsystem, and then we ask for an id from user
//we pass that id into login() and get a true or false of if valid, haina
//so then if false we'll be like bruh give a correct password
//if true to we have to see what type of user has logined
//to i finking, we make some function in system class, where we pass the id and we find id from the array and store everything from there to the pointer logined user (pssss i made a function in system, i.e. logAUser(string id) )
//this will make our life very very easier pleaseeeeee9