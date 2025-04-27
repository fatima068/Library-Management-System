#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
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
    System() {
        loadBooks();
        loadNormalUsers();
    }

    bool isUserIDunique(string id) {
        for (int i = 0; i<allUsers.size(); i++) {
            if (allUsers[i]->userID == id) {
                return false;
            }
        }
        return true;
    }

    void logineduserworks () {
        cout << "oke now we display the details of the user who loggened in\n" << loginedUser << endl << "yayyy hogya display haina?\n"; //deepseek saying ke make it cout << *loginedUser, but uss se weird error aara
        cout << "oke now lets see all users\n";
        for (int i = 0; i < allUsers.size(); i++) {
            cout << i + 1 << endl << allUsers[i] << endl;
        }
    }

    void signUp() {
        char userType;
        cout << "Enter type of user to register: P(premium), N(normal), L(librarian): ";
        cin >> userType;
        cin.ignore(1000, '\n');
        switch (userType) {
            case 'P':
            case 'p': {
                // taking input of inofrmation of new user
                string userID, username, contactNum;
                cout << "enter the following information to register a new user: " << endl;
                cout << "user id(eg. P001, P333 ....): ";
                getline(cin, userID);
                // load premium users to check that id user entered is unique
                loadPremiumUsers();
                while (!isUserIDunique(userID) || userID.length() != 4 || userID.at(0) != 'P') {
                    cout << "user id taken or invalid format! Enter new id(P000, P001, etc): ";
                    getline(cin, userID);
                }
                cout << "enter your name: ";
                getline(cin, username);
                cout << "enter contact number: ";
                getline(cin, contactNum);
                // create user object then call addToFile function for this user to append them to the end of premium users file 
                User* u1 = new PremiumUser(userID, username, contactNum);
                // then get their password, encode it, and add to login.txt file 
                string password = loginSystem.getPassword();
                loginSystem.encode(password);
                ofstream loginFile("textFiles/login.txt", ios::app);
                string line = userID + " " + password;
                loginFile << line << endl;
                loginFile.close();
                u1->addUserToFile();
                cout << "premium user " << userID << " added successfully" << endl;
                break;
            }

            case 'N':
            case 'n': {
                // taking input of inofrmation of new user
                string userID, username, contactNum;
                cout << "enter the following information to register a new user: " << endl;
                cout << "user id(eg N000, N001, ....): ";
                getline(cin, userID);
                // load normal users to check that id user entered is unique
                loadNormalUsers();
                while (!isUserIDunique(userID) || userID.length() != 4 || userID.at(0) != 'N') {
                    cout << "user id taken or invalid format! Enter new id(N000, N001, etc): ";
                    getline(cin, userID);
                }
                cout << "enter your name: ";
                getline(cin, username);
                cout << "enter contact number: ";
                getline(cin, contactNum);
                // create user object then call addToFile function for this user to append them to the end of premium users file 
                User* u1 = new NormalUser(userID, username, contactNum);
                // then get their password, encode it, and add to login.txt file 
                string password = loginSystem.getPassword();
                loginSystem.encode(password);
                ofstream loginFile("textFiles/login.txt", ios::app);
                string line = userID + " " + password;
                loginFile << line << endl;
                loginFile.close();
                u1->addUserToFile();
                cout << "normal user " << userID << " added successfully" << endl;
                break;
            }

            case 'L':
            case 'l': {
                // taking input of inofrmation of new user
                string userID, username, contactNum;
                float salary;
                cout << "enter the following information to register a new user: " << endl;
                cout << "user id(eg. L001, L333 ....): ";
                getline(cin, userID);
                // load premium users to check that id user entered is unique
                loadPremiumUsers();
                while (!isUserIDunique(userID) || userID.length() != 4 || userID.at(0) != 'P') {
                    cout << "user id taken or invalid format! Enter new id(L000, L001, etc): ";
                    getline(cin, userID);
                }
                cout << "enter your name: ";
                getline(cin, username);
                cout << "enter contact number: ";
                getline(cin, contactNum);
                cout << "enter salary: ";
                cin >> salary;
                // create user object then call addToFile function for this user to append them to the end of premium users file 
                User* u1 = new Librarian(userID, username, contactNum, salary);
                // then get their password, encode it, and add to login.txt file 
                string password = loginSystem.getPassword();
                loginSystem.encode(password);
                ofstream loginFile("textFiles/login.txt", ios::app);
                string line = userID + " " + password;
                loginFile << line << endl;
                loginFile.close();
                u1->addUserToFile();
                cout << "librarian " << userID << " added successfully" << endl;
                break;
            }

            default:
                cout << "invalid user type" << endl;
                break;
        }
    }

    void logAUser(string id) {
        cout << "login a user func starts here\n";
        for (int i = 0; i < allUsers.size(); i++) {
            if (id == allUsers[i]->userID) {
                cout << allUsers[i];
                loginedUser = allUsers[i];
                break;
            }
        }
        cout << "login a user func ends here\n";
    }

    char getCurrentUserType() {
        return loginSystem.getUserType();
    }

    bool loginUser(string id) {
        return loginSystem.login(id);
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
        ofstream allBooksFile("textFiles/allBooks.txt", ios::trunc);
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }
        int i;

        for (i = 0; i < allBooks.size(); i++) {
            allBooks[i].addBookToFile();
        }
        allBooksFile.close();
        cout << "saved " << i << " books" << endl;
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
        cout << "Loaded " << allUsers.size() << " premium users" << endl;
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
        cout << "Loaded " << allUsers.size() << " normal users" << endl;
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
            float salary = stof(userData[3]);

            Librarian* lUser = new Librarian(userData[0], userData[1], userData[2], salary); 
            allUsers.push_back(lUser);
        }
        librariansFile.close();
        cout << "Loaded " << allUsers.size() << " librarians" << endl;
    }

    void saveUsers() {
        if (loginSystem.getUserType() == 'L') {
            ofstream librariansFile("textFiles/librarians.txt", ios::trunc);
            librariansFile.close();
            if (!librariansFile) {
                cerr << "Error in opening all books file" << endl;
                return;
            }
            for (int i = 0; i < allUsers.size(); i++) {
                allUsers[i]->addUserToFile();
            }
            librariansFile.close();
        }

        else if (loginSystem.getUserType() == 'P') {
            // open the file in trunc mode just erase all existing data in it, then call add user to file for each array element 
            ofstream premiumUsersFile("textFiles/premiumUsers.txt", ios::trunc);
            premiumUsersFile.close();
            if (!premiumUsersFile) {
                cerr << "Error in opening all books file" << endl;
                return;
            }
    
            for (int i = 0; i < allUsers.size(); i++) {
                allUsers[i]->addUserToFile();
            }
            premiumUsersFile.close();
        }

        else if (loginSystem.getUserType() == 'N') {
            ofstream normalUserFile("textFiles/normalUsers.txt", ios::trunc);
            normalUserFile.close();
            if (!normalUserFile) {
                cerr << "Error in opening all books file" << endl;
                return;
            }
    
            for (int i = 0; i < allUsers.size(); i++) {
                allUsers[i]->addUserToFile();
            }
            normalUserFile.close();
        }
        else {
            cout << "login to access functions" << endl;
        }
    }

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

    void borrowBook() { 
        string idToBorrow;
        cout << "enter Book ID of book you want to borrow: ";
        cin.ignore();
        getline(cin, idToBorrow);
        // check if book is not already borrowed by other user 
        string temp =  "..." + idToBorrow + "...";
        cout << "book id: " << temp <<endl; 
        for (int i = 0; i<allBooks.size(); i++) {
            if (allBooks[i].bookID == idToBorrow) {
                bool flag = allBooks[i].borrowBook();
                cout << "oke so boook class fing hgya hai ab user" <<endl;
                if (flag) {
                    cout << "oflag true now user class function will be called" <<endl;
                    loginedUser->borrowBook(idToBorrow);
                    cout << "oke hogya user ka kaam done bye" <<endl;
                    return;
                }
            }
        }
        cout << "book id not found in system" << endl;
    }

    void returnBook() {

    }

    void deleteUserAccount() {     
        string idToRemove;
        char userType;
        bool flag = false;
        cout << "enter user ID to remove: ";
        cin.ignore();
        getline(cin, idToRemove);
        cout << "enter user type to remove: ";
        cin >> userType;

        if (userType == 'p'|| userType == 'P' ) {
                ifstream premUsers("textFiles/premiumUsers.txt");
                if (!premUsers) {
                    cerr << "Error opening file: " << endl;
                    return;
                }

                ofstream tempFile("temp.txt");
                if (!tempFile) {
                    cerr << "Error creating temporary file." << endl;
                    premUsers.close();
                    return;
                }

                string line;
                bool found = false;
                int linesToSkip = 0;

                while (getline(premUsers, line)) {
                    if (linesToSkip > 0) {
                        linesToSkip--;
                        continue;
                    }

                    if (line == idToRemove) {
                        // Found the record to remove - skip next 13 lines
                        found = true;
                        linesToSkip = 13;
                        continue;
                    }

                    tempFile << line << endl;
                }

                premUsers.close();
                tempFile.close();

                if (found) {
                // Delete original file and rename temp file
                if (remove("textFiles/premiumUsers.txt") != 0) {
                    cerr << "Error deleting original file." << endl;
                    return;
                }
                if (rename("temp.txt", "textFiles/premiumUsers.txt") != 0) {
                    cerr << "Error renaming temporary file." << endl;
                    return;
                }
                cout << "Record with ID " << idToRemove << " removed successfully." << endl;
            } else {
                cout << "Record with ID " << idToRemove << " not found." << endl;
                remove("temp.txt"); // Clean up temp file
            }
        }

        if (userType == 'n' || userType == 'N') {
                ifstream normUsers("textFiles/normalUsers.txt");
                if (!normUsers) {
                    cerr << "Error opening file: " << endl;
                    return;
                }

                ofstream tempFile("temp.txt");
                if (!tempFile) {
                    cerr << "Error creating temporary file." << endl;
                    normUsers.close();
                    return;
                }

                string line;
                bool found = false;
                int linesToSkip = 0;

                while (getline(normUsers, line)) {
                    if (linesToSkip > 0) {
                        linesToSkip--;
                        continue;
                    }

                    if (line == idToRemove) {
                        // Found the record to remove - skip next 6 lines
                        found = true;
                        linesToSkip = 6;
                        continue;
                    }

                    tempFile << line << endl;
                }

                normUsers.close();
                tempFile.close();

                if (found) {
                // Delete original file and rename temp file
                if (remove("textFiles/normalUsers.txt") != 0) {
                    cerr << "Error deleting original file." << endl;
                    return;
                }
                if (rename("temp.txt", "textFiles/normalUsers.txt") != 0) {
                    cerr << "Error renaming temporary file." << endl;
                    return;
                }
                cout << "Record with ID " << idToRemove << " removed successfully." << endl;
            } else {
                cout << "Record with ID " << idToRemove << " not found." << endl;
                remove("temp.txt"); // Clean up temp file
            }

        }

        if (userType == 'l' || userType == 'L') {
            ifstream librarians("textFiles/librarians.txt");
                if (!librarians) {
                    cerr << "Error opening file: " << endl;
                    return;
                }

                ofstream tempFile("temp.txt");
                if (!tempFile) {
                    cerr << "Error creating temporary file." << endl;
                    librarians.close();
                    return;
                }

                string line;
                bool found = false;
                int linesToSkip = 0;

                while (getline(librarians, line)) {
                    if (linesToSkip > 0) {
                        linesToSkip--;
                        continue;
                    }

                    if (line == idToRemove) {
                        // Found the record to remove - skip next 3 lines
                        found = true;
                        linesToSkip = 3;
                        continue;
                    }

                    tempFile << line << endl;
                }

                librarians.close();
                tempFile.close();

                if (found) {
                // Delete original file and rename temp file
                if (remove("textFiles/librarians.txt") != 0) {
                    cerr << "Error deleting original file." << endl;
                    return;
                }
                if (rename("temp.txt", "textFiles/librarians.txt") != 0) {
                    cerr << "Error renaming temporary file." << endl;
                    return;
                }
                cout << "Record with ID " << idToRemove << " removed successfully." << endl;
            } else {
                cout << "Record with ID " << idToRemove << " not found." << endl;
                remove("temp.txt"); // Clean up temp file
            }

        }

        for (int i = 0; i < allUsers.size(); i++) {
            if (allUsers[i]->userID == idToRemove) {
                delete allUsers[i];
                allUsers.erase(allUsers.begin() + i);
                cout << "user " << idToRemove << " removed successfully" << endl;
                flag = true;
                break;
            }
        }

        if (!flag) {
            cout << "User not found" << endl;
        }
    }

    void LibrarianMenu() {
        int choice = -1;
        while(choice != 7) {
            cout << "1. search book\n2. search user\n3. delete a user account\n4. view book list\n5. add new book to library\n6. remove a book\n7. logout\nenter your choice: ";
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
                    deleteUserAccount();
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
                    saveBooks();
                    saveUsers();
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
        while(choice != 8) {
            cout << "1. search book\n2. view book list\n3. borrow book\n4. return book\n5. pay fine\n6. renew book \n7. display borrowed books\n8. exit\nenter your choice: ";
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
                    cout << "1. view all books\n2. view available books\nenter your choice: ";
                    cin >> choice3; 
                    switch (choice3) {
                        case 1: {
                            displayAllBooks();
                            break;
                        }
                        case 2: {
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
                borrowBook();
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

            case 7: { // display borrowed books
                loginedUser->displayBooksBorrowed();
                break;
            }

            case 8: {
                saveBooks();
                saveUsers();
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