#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "allClasses.hpp"
#include "login.hpp"
using namespace std;

class System {
    private:
    vector<User*> allUsers;
    vector<Book> allBooks;
    User* loginedUser;
    LoginSystem loginSystem;

    public:
    void logAUser(string id) { // will this work lets hope it does lmao
        for (int i = 0; i < allUsers.size(); i++) {
            if (id == allUsers[i]->userID) {
                loginedUser = allUsers[i];
            }
        }
    }

    void searchBookName() {
        string nameToSearch;
        cout << "enter book name to search: ";
        
        getline(cin, nameToSearch);
        cout << endl;

        bool flag = false;
        for (int i = 0; i < allBooks.size(); i++) { 
            if (allBooks[i].title == nameToSearch) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    } 
    
    void searchAuthorName() {
        string authorToSearch;
        cout << "enter author to search: ";
        getline(cin, authorToSearch);
        cout << endl;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].author == authorToSearch) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    }

    void searchBookId() {
        string bookIDtoSearch;
        cout << "enter book id to search: "; 
        getline(cin, bookIDtoSearch);
        cout << endl;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].bookID == bookIDtoSearch) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    }
    
    void searchUserName() {
        string nameToSearch;
        cout << "enter user name to search: ";
        getline(cin, nameToSearch);
        cout << endl;
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->name == nameToSearch) {
                cout << allUsers[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl << endl;
        } 
    }
    
    void searchUserId() {
        string idToSearch;
        cout << "enter user id to search: ";
        getline(cin, idToSearch);
        cout << endl;
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->userID == idToSearch) {
                cout << allUsers[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl << endl;
        } 
    }

    // User* findUser(const string& userID) {
    //     for (User* user : allUsers) {
    //         if (user->userID == userID) {
    //             return user;
    //         }
    //     }
    //     return nullptr;
    // } 

    void loadBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }
    
        string bookData[10]; 
        
        while (getline(allBooksFile, bookData[0])) {  // Read bookID
            // Read the remaining 7 fields
            for (int i = 1; i < 10; i++) {
                if (!getline(allBooksFile, bookData[i])) {
                    cerr << "Incomplete book record" << endl;
                    return;
                }
            }
    
            bool borrow = (bookData[5] == "true"); // convert string to bool
            int dd = stoi(bookData[6]);
            int mm = stoi(bookData[7]); 
            int yy = stoi(bookData[8]); 
            
            int timesRenewed = stoi(bookData[9]);  // convert string to int
    
            // Create and store the book
            Book temp(bookData[0], bookData[1], bookData[2], bookData[3], bookData[4], borrow, dd, mm, yy, timesRenewed);
            allBooks.push_back(temp);
        }
        
        allBooksFile.close();
        cout << "Loaded " << allBooks.size() << " books" << endl;
    }

    void saveBooks() {
        ofstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }

        for (int i = 0; i < allBooks.size(); i++) {
            allBooks[i].addBookToFile();
        }
        allBooksFile.close();
    }
        
    void loadPremiumUsers() {
        ifstream premiumFile("textFiles/premiumUsers.txt");
        if (!premiumFile) {
            cerr << "Error in opening premium users file" << endl; 
            return; 
            
        }
        string userData[16]; // userID, name, contactNum, maxbooks, borrowedBooks(), fineperday, totalFines, 
        string line; 

        while (getline(premiumFile, userData[0])) { // Read userID (first field)
            // Read the remaining basic fields
            for (int i = 1; i < 14; i++) {
                if (!getline(premiumFile, userData[i])) {
                    cerr << "Incomplete user record" << endl;
                    return;
                }
            }
    
            // create appropriate user object for premium user
            float fine = stof(userData[13]);
            string arr[10];
            int j = 3;
            for (int i = 0; i<10; i++) {
                arr[i] = userData[j];
                j++;
            }
            
            PremiumUser* pUser = new PremiumUser(userData[0], userData[1], userData[2], arr, fine);
            allUsers.push_back(pUser);
        }
        
        premiumFile.close();
        cout << "Loaded " << allUsers.size() << " users" << endl;
    }

    void loadNormalUsers() {
        ifstream normalFile("textFiles/normalUsers.txt");
        if (!normalFile) {
            cerr << "Error in opening normal users file" << endl; 
            return; 
        }
        string userData[7]; // userID, name, contactNum, borrowedBooks(), totalFines, 
        string line;
        while (getline(normalFile, userData[0])) { // Read userID (first field)
            // Read the remaining basic fields
            for (int i = 1; i < 7; i++) {
                if (!getline(normalFile, userData[i])) {
                    cerr << "Incomplete user record" << endl;
                    return;
                }
            }
    
            // create appropriate user object for premium user
            float fine = stof(userData[6]);
            string arr[3];
            int j = 3;
            for (int i = 0; i<3; i++) {
                arr[i] = userData[j];
                j++;
            }
            
            NormalUser* nUser = new NormalUser(userData[0], userData[1], userData[2], arr, fine);    
            allUsers.push_back(nUser);
        }
        
        normalFile.close();
        cout << "Loaded " << allUsers.size() << " users" << endl;
    }
    
    void loadLibrarian() {
        ifstream librariansFile("textFiles/librarians.txt");
        if (!librariansFile) {
            cerr << "Error in opening librarians file" << endl; 
            return; 
            
        }
        string userData[4]; // userID, name, contactNum, monthlySalary
        string line;

         while (getline(librariansFile, userData[0])) { // Read userID (first field)
            // Read the remaining basic fields
            for (int i = 1; i < 4; i++) {
                if (!getline(librariansFile, userData[i])) {
                    cerr << "Incomplete user record" << endl;
                    return;
                }
            }

            Librarian* lUser = new Librarian(userData[0], userData[1], userData[2], stof(userData[3])); // yaar this constuctor is weird because like ismai write to file bhi hora uween i dont get
            allUsers.push_back(lUser);
            // Skip empty line between user records if exists
            getline(librariansFile, line);
        }
        librariansFile.close();
        cout << "Loaded " << allUsers.size() << " users" << endl;
    }
     

    // void loadUsers() { 
    //     ifstream allUsersFile("textFiles/allUsers.txt");
    //     if (!allUsersFile) {
    //         cerr << "Error in opening all users file" << endl; 
    //         return; 
            
    //     }
    
    //     string userData[5]; // userID, name, contactNum, type-specific field, borrowed books count
    //     string line;
        
    //     while (getline(allUsersFile, userData[0])) { // Read userID (first field)
    //         // Read the remaining basic fields
    //         for (int i = 1; i < 4; i++) {
    //             if (!getline(allUsersFile, userData[i])) {
    //                 cerr << "Incomplete user record" << endl;
    //                 return;
    //             }
    //         }
    
    //         // Determine user type and create appropriate user object
    //         char userType = userData[0][0]; // First character of userID indicates type
            
    //         if (userType == 'P') { // Premium User
    //             PremiumUser* pUser = new PremiumUser(userData[0], userData[1], userData[2]);
    //             pUser->totalFines = stof(userData[3]);
                
    //             // Load borrowed books count
    //             getline(allUsersFile, line);
    //             int borrowedCount = stoi(line);
                
    //             // Load borrowed books IDs
    //             for (int i = 0; i < borrowedCount; i++) {
    //                 getline(allUsersFile, line); // book ID
    //                 // Note: Actual book objects would need to be linked from allBooks vector
    //             }
                
    //             allUsers.push_back(pUser);
    //         }
    //         else if (userType == 'N') { // Normal User
    //             NormalUser* nUser = new NormalUser(userData[0], userData[1], userData[2]);
    //             nUser->totalFines = stof(userData[3]);
                
    //             // Load borrowed books count
    //             getline(allUsersFile, line);
    //             nUser->currentBooksBorrowed = stoi(line);
                
    //             // Load borrowed books IDs
    //             for (int i = 0; i < nUser->currentBooksBorrowed; i++) {
    //                 getline(allUsersFile, line); // book ID
    //                 // Note: Actual book pointers would need to be linked from allBooks vector
    //             }
                
    //             allUsers.push_back(nUser);
    //         }
    //         else if (userType == 'L') { // Librarian
    //             Librarian* lUser = new Librarian(userData[0], userData[1], userData[2], stof(userData[3]));
    //             allUsers.push_back(lUser);
    //         }
            
    //         // Skip empty line between user records if exists
    //         getline(allUsersFile, line);
    //     }
        
    //     allUsersFile.close();
    //     cout << "Loaded " << allUsers.size() << " users" << endl;
    // }
    
    // void saveUsers() {
    //     ofstream allUsersFile("textFiles/allUsers.txt");
    //     if (!allUsersFile) {
    //         cerr << "Error in opening all users file" << endl;
    //         return;
    //     }
    
    //     for (User* user : allUsers) {
    //         char userType = user->userID[0];
            
    //         // Write common user fields
    //         allUsersFile << user->userID << endl;
    //         allUsersFile << user->name << endl;
    //         allUsersFile << user->contactNum << endl;
    
            // if (userType == 'P') {
            //     PremiumUser* pUser = dynamic_cast<PremiumUser*>(user);
            //     allUsersFile << pUser->totalFines << endl;
            //     allUsersFile << pUser->borrowedBooks.size() << endl;
                
            //     // Write borrowed books IDs
            //     for (const string book : pUser->borrowedBooks) {
            //         allUsersFile << book << endl;
            //     }
            // }
    //         else if (userType == 'N') {
    //             NormalUser* nUser = dynamic_cast<NormalUser*>(user);
    //             allUsersFile << nUser->totalFines << endl;
    //             allUsersFile << nUser->currentBooksBorrowed << endl;
                
    //             // Write borrowed books IDs
    //             for (Book* book : nUser->borrowedBooks) {
    //                 if (book) {
    //                     allUsersFile << book->bookID << endl;
    //                 }
    //             }
    //         }
    //         else if (userType == 'L') {
    //             Librarian* lUser = dynamic_cast<Librarian*>(user);
    //             allUsersFile << lUser->monthlySalary << endl;
    //         }
            
    //         // Separate user records with empty line
    //         allUsersFile << endl;
    //     }
        
    //     allUsersFile.close();
    // }

    void displayAllBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            cout << allBooks[i];
        }
    }

    void displayBorrowedBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].isBorrowed)
                cout << allBooks[i];
        }
    }

    void displayAvailableBooks() {
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            if (!allBooks[i].isBorrowed)
                cout << allBooks[i];
        }
    }

    void displayUserBorrowedBooks() {
        //oke so we make a function for this in users 
        loginedUser->displayBooksBorrowed();
    }

    void borrowBook() { 
        // string id;
        // cout << "enter Book ID of book you want to borrow: ";
        // cin >> id;
        // if (loginedUser->isBookBorrowed(id)) {
        //     cout << "You have already borrowed the Book" << endl;
        //     return;
        // }

        // for (int i = 0; i < allBooks.size(); i++) {
        //     if (id == allBooks[i].bookID) {
        //         allBooks[i].borrowBook();
        //         return;
        //     }
        // }
        // cout << "Book ID doesn't exist" << endl;
    }

    void returnBook() {

    }

    // becuase one user will be logged in at one time, just fetch that user from the file instead of fetching all users, but then librarian mei seach users function wont work, so what if we remove that function? or just fetch the records of the user that the librarian has searched for ? maybe this would work  

    // void loadUsers() {}

    // void saveUsers() { // jo hum kar r
    //     ofstream allUsersFile("textFiles/allUsers.txt");
    //     if (!allUsersFile) {
    //         cerr << "Error in opening all users file" << endl;
    //         return;
    //     }

    //     for (int i = 0; i < allUsers.size(); i++) {
    //         // allUsers[i]->addUserToFile(); 
    //     }
    //     allUsersFile.close();
    // }

    void mainMenu() {
        // now over here give 2 option: login or signup
        // login functionality has been made, need to make sign up (basically registering a new user)'
        // first make load user and save user maybe ? 
        
        string userID;
        cout << "Enter user ID: ";
        getline(cin, userID);
        if (loginSystem.login(userID)) {
            logAUser(userID);
            loadBooks();
            
            // Determine user type and show appropriate menu
            char userType = loginSystem.getUserType();
            
            if (userType == 'L') { // Librarian
                cout << "\n=== LIBRARIAN MENU ===" << endl;
                LibrarianMenu();
            } 
            else { // Normal or Premium User
                cout << "\n=== USER MENU ===" << endl;
                userMenu();
            }
        } else {
            cout << "Login failed. Exiting..." << endl;
            saveBooks();
            exit(0);
        }
    }

    void LibrarianMenu() {
        int choice = -1;
        while(choice != 7) {
            cout << "1. search book\n2. search user\n3. delete a user account\n4. view book list\n5. add new book to library\n6. remove a book\n 7. logout\nenter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: { // search book
                    int choice1; 
                    cout << "1. by book name\n2. by author name\n3. by book id\nenter your choice: ";
                    cin >> choice1;
                    switch (choice1) {
                        case 1: { 
                            cin.ignore();
                            searchBookName();
                            break;
                        }
                        
                        case 2: {
                            cin.ignore();
                            searchAuthorName();
                            break;
                        }
                         
                        case 3: { 
                            cin.ignore();
                            searchBookId();
                            break;
                        }
                        
                        default:
                            cout << "wrong choice " << endl; 
                            break;
                    }
                    break;
                }

                case 2: { // search user
                    int choice2; 
                    cout << "1. by user name\n2. by user id\nenter your choice: ";
                    cin >> choice2;
                    switch (choice2) {
                        case 1: {
                            cin.ignore();
                            searchUserName(); 
                            break;
                        }

                        case 2: {
                            cin.ignore();
                            searchUserId();
                            break;
                        }

                        default:
                            cout << "wrong choice" << endl; 
                            break;
                    }
                    break;
                }

                case 3: { // delete user account
                    break;
                }

                case 4: { // view book list
                    int choice3; 
                    cout << "1. view all books\n2. view borrowed books\n3. view available books\nenter your choice: ";
                    cin >> choice3; 
                    switch (choice3) {
                        case 1: {
                            displayAllBooks();
                            break;
                        }
                        case 2: {
                            displayBorrowedBooks();
                            break;
                        }
                        case 3: {
                            displayAvailableBooks(); 
                            break;
                        }

                        default:
                            cout << "invalid choice " << endl; 
                            break;
                    }
                    break;
                }

                case 5: { // add new book to library
                    string id, isbn, title, author, genre;
                    cout << "Enter book details of book to add" << endl;
                    cout << "Book ID: "; // should i first check if its unique ?  
                    //yesh
                    cin.ignore();
                    getline(cin, id);
                    cout << "ISBN: ";
                    getline(cin, isbn);
                    cout << "Title: ";
                    getline(cin, title);
                    cout << "Author: ";
                    getline(cin, author);
                    cout << "Genre: ";
                    getline(cin, genre);
                    Book b1 = Book(id, isbn, title, author, genre, false, 0, 0, 0);
                    allBooks.push_back(b1);
                    break;
                }

                case 6: { // remove a book
                    string idToRemove;
                    bool flag = false;
                    cout << "enter book id of book to remove: ";
                    cin.ignore();
                    getline(cin, idToRemove);
                    for (int i = 0; i < allBooks.size(); i++) {
                        if (allBooks[i].bookID == idToRemove) {
                            allBooks.erase(allBooks.begin() + i);
                            cout << "book " << idToRemove << " removed successfully" << endl;
                            flag = true;
                            break;
                        }
                    }
                    if (flag == false) {
                        cout << "book not found" << endl;
                    }
                    break;
                }

                case 7: {
                    cout << "logging out..." << endl; 
                    saveBooks();
                    loginSystem.logout();
                    break;
                }

                default:
                    cout << "wrong choice" << endl; 
                    break;
            }
        }
    }

    

    void userMenu() {
        int choice = -1;
        while(choice != 7) {
            cout << "1. search book\n2. view book list\n3. borrow book\n4. return book\n5. pay fine\n6. renew book \n7. exit\nenter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: { // search book
                    int choice1; 
                    cout << "1. by book name\n2. by author name\n3. exit\nenter your choice: ";
                    cin >> choice1;
                    switch (choice1) {
                        case 1: {
                            cin.ignore();
                            searchBookName();
                            break;
                        }
                        case 2: {
                            cin.ignore();
                            searchAuthorName();
                            break;
                        } 

                        case 3: {
                            cout << "exiting book search menu" << endl;
                            break;
                        }

                        default:
                            cout << "wrong choice " << endl; 
                            break;
                    }
                    break;
            }

            case 2: { // view book list
                    int choice3; 
                    cout << "1. view all books\n2. view borrowed books\n3. view available books\nenter your choice: ";
                    cin >> choice3; 
                    switch (choice3) {
                        case 1: {
                            displayAllBooks();
                            break;
                        }
                        case 2: {
                            // displayUserBorrowedBooks(); // remove this maybe because does user even need to know borrowed books alag se like this ? 
                            break;
                        }
                        case 3: {
                            displayAvailableBooks(); 
                            break;
                        }

                        default:
                            cout << "invalid choice " << endl; 
                            break;
                    }
                    break;
            }

            case 3: { //borrow book
                // borrowBook();
                break;
            }

            case 4: { //return book
                
                // something about pointers is confusing. maybe try removing pointers from user class return book function by calling return book for both book and user in system class instead of in user class by passing book as pointer

                // string idToReturn;
                // Book* b1;
                // cout << "enter id of book to return: ";
                // getline(cin, idToReturn);
                // for (int i=0; i<allBooks.size(); i++) {
                //     if (allBooks[i].bookID == idToReturn) {
                //         allBooks[i].returnBook();
                //     }
                // }
                // loginedUser->returnBook(b1);
                break;
            }

            case 5: { //pay fine
                //this can be done yahin pe ma
                cin.ignore();
                loginedUser->payFine();
                break;
            }

            case 6: { //renew book
                // loginedUser->renewBook()

                // try removing pointers from here as well. 
                // what we can do is edit user to rmeove or include books borrowed by them separately, then search for book id in all books vector and edit that separately over here, no need to make a sepaarte function because function not a part of librarian class.
                break;
            }

            case 7: {
                saveBooks();
                loginSystem.logout();
                break;
            }

            default:
                cout << "wrong choice" << endl; 
                break;
            }
        }
    }


    ~System() {
        for (User* user : allUsers) {
            delete user;
        }
        
    }
};

#endif

// search user by id
// search book by name (done)
// search book by author (done)
// search book by genre (kinda done)
// search book by id (done)
// create a new user 
// delete user from system 
// view all available books (done)
// view all borrowed books (done)
// renew a borrowed book
// session management and axxess control seekhn hai 
