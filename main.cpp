#include <iostream>
#include "login.hpp"
#include "bookClass.hpp"
#include "userClasses.hpp"
using namespace std;

int main() {
    cout << "=== Testing Library Management System ===\n\n";

    // 1. Test Book functionality
    cout << "1. Testing Book Class:\n";
    Book testBook("B001", "9783161484100", "Sample Book", "Test Author", "Fiction", false, 0, 0, 0);
    
    cout << "- Trying to borrow book:\n";
    testBook.borrowBook();  // Should succeed
    
    cout << "- Trying to borrow again:\n";
    testBook.borrowBook();  // Should fail (already borrowed)
    
    cout << "- Returning book:\n";
    testBook.returnBook();  // Should succeed
    
    cout << "- Trying to return again:\n";
    testBook.returnBook();  // Should fail (not borrowed)
    
    // 2. Test Date comparison
    cout << "\n2. Testing Date Comparison:\n";
    Date today = dateTodayFunc();
    Date pastDate(today.dd-2, today.mm, today.yy); // 2 days ago
    Date futureDate(today.dd+2, today.mm, today.yy); // 2 days in future
    
    cout << "- Comparing with past date: " 
         << compareDate(pastDate) << " days overdue (should be 2)\n";
    cout << "- Comparing with future date: " 
         << compareDate(futureDate) << " days overdue (should be 0)\n";

    // 3. Test Login System
    cout << "\n3. Testing Login System:\n";
    LoginSystem login;
    
    cout << "Attempting login (enter test credentials):\n";
    if (login.login()) {
        cout << "- Login successful! User type: " << login.getUserType() << endl;
        cout << "- Testing logout (will exit program):\n";
        login.logout(); // This will exit
    } else {
        cout << "- Login failed (as expected for invalid credentials)\n";
    }

    cout << "\nAll tests completed!\n";
    return 0;
}

// // Add all edited files to Git and commit them
//     // Hit Ctrl + Shift + A (PC) / Cmd + Shift + A (Mac).
// // Push local commits
//     // Hit Ctrl + Shift + X (PC) / Cmd + Shift + X (Mac).