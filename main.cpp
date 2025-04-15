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
         << testBook.getDaysOverdue() << " days overdue (should be 2)\n";
    cout << "- Comparing with future date: " 
         << testBook.getDaysOverdue() << " days overdue (should be 0)\n";

    // 3. Test Login System
    // cout << "\n3. Testing Login System:\n";
    // LoginSystem login;
    
    // cout << "Attempting login (enter test credentials):\n";
    // if (login.login()) {
    //     cout << "- Login successful! User type: " << login.getUserType() << endl;
    //     cout << "- Testing logout (will exit program):\n";
    //     login.logout(); // This will exit
    // } else {
    //     cout << "- Login failed (as expected for invalid credentials)\n";
    // } 

    // 4. Test User Classes
    cout << "\n4. Testing User Classes:\n";
    
    // Create test books
    Book* book1 = new Book("B001", "1111111111111", "Book 1", "Author 1", "Fiction", false, 0, 0, 0); 
    Book* book2 = new Book("B002", "2222222222222", "Book 2", "Author 2", "Non-Fiction", false, 0, 0, 0);
    Book* book3 = new Book("B003", "3333333333333", "Book 3", "Author 3", "Science", false, 0, 0, 0);
    Book* book4 = new Book("B004", "4444444444444", "Book 4", "Author 4", "History", false, 0, 0, 0);
    
    // Test Premium User
    cout << "\n- Testing Premium User:\n";
    PremiumUser premiumUser("P001", "Premium User", "1234567890");
    
    cout << "Borrowing books (limit 10):\n";
    premiumUser.borrowBook(book1);
    premiumUser.borrowBook(book2);
    premiumUser.borrowBook(book3);
    premiumUser.borrowBook(book4);
    
    cout << "\nTrying to return books:\n";
    premiumUser.returnBook(book3);
    premiumUser.returnBook(book2);
    
    // Test Normal User
    cout << "\n- Testing Normal User:\n";
    NormalUser normalUser("N001", "Normal User", "9876543210");
    
    cout << "Borrowing books (limit 3):\n";
    normalUser.borrowBook(book1);
    normalUser.borrowBook(book2);
    normalUser.borrowBook(book3);
    normalUser.borrowBook(book4); // Should fail (limit reached)
    
    cout << "\nTrying to return books:\n";
    normalUser.returnBook(book1);// Should fail (didn't borrow book1)
    normalUser.returnBook(book2);
    normalUser.returnBook(book3); 
    
    // Test Librarian
    cout << "\n- Testing Librarian:\n";
    Librarian librarian("L001", "Library Admin", "5555555555", 5000.00);
    
    cout << "Trying to borrow/return books:\n";
    librarian.borrowBook(book1); // Should fail
    librarian.returnBook(book1); // Should fail

    cout << "\nAll tests completed!\n";
    delete book1;
    delete book2;
    delete book3;
    delete book4;
    return 0;
}