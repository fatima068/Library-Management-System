#include <iostream>
#include "system.hpp"
using namespace std;

int main() {
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