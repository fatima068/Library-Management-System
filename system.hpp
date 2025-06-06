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
    LoginSystem loginSystem;

    public:
    bool isUserIDunique(string id) {
        for (int i = 0; i<allUsers.size(); i++) {
            if (allUsers[i]->userID == id) {
                return false;
            }
        }
        return true;
    }

    bool isBookIDunique(string id) {
        for (int i = 0; i<allBooks.size(); i++) {
            if (allBooks[i].bookID == id) {
                return false;
            }
        }
        return true;
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
                ofstream premiumFile("textFiles/premiumUsers.txt", ios::app);
                u1->addUserToFile(premiumFile);
                cout << "premium user " << userID << " added successfully" << endl;
                premiumFile.close();
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
                ofstream normalFile("textFiles/normalUsers.txt", ios::app);
                u1->addUserToFile(normalFile);
                cout << "normal user " << userID << " added successfully" << endl;
                normalFile.close();
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
                loadLibrarian();
                while (!isUserIDunique(userID) || userID.length() != 4 || userID.at(0) != 'L') {
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
                ofstream librarianFile("textFiles/librarians.txt", ios::app);
                u1->addUserToFile(librarianFile);
                cout << "librarian " << userID << " added successfully" << endl;
                librarianFile.close();
                break;
            }

            default:
                cout << "invalid user type" << endl;
                break;
        }
    }

    int loginedUserIndex(string id) {
        for (int i = 0; i < allUsers.size(); i++) {
            if (id == allUsers[i]->userID) {
                return i;
            }
        }
        cout << "unable to log user " << endl;
        return -1;
    }

    char getCurrentUserType() { return loginSystem.userType; }
    bool loginUser(string id) { return loginSystem.login(id); }

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

    void searchBookId(string id) {
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].bookID == id) {
                cout << allBooks[i] << endl;
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl << endl;
        }
    }

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
    
            bool borrow = (bookData[5] == "true");
            int dd = stoi(bookData[6]);
            int mm = stoi(bookData[7]); 
            int yy = stoi(bookData[8]); 
            
            int timesRenewed = stoi(bookData[9]);
    
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

        while (getline(premiumFile, userData[0])) { 
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
        while (getline(normalFile, userData[0])) {
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

         while (getline(librariansFile, userData[0])) { 
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
        if (loginSystem.userType == 'L') {
            ofstream librariansFile("textFiles/librarians.txt", ios::trunc);
            if (!librariansFile) {
                cerr << "Error in opening all books file" << endl;
                return;
            }
            for (int i = 0; i < allUsers.size(); i++) {
                allUsers[i]->addUserToFile(librariansFile);
            }
            librariansFile.close();
        }

        else if (loginSystem.userType == 'P') {
            // open the file in trunc mode just erase all existing data in it, then call add user to file for each array element 
            ofstream premiumUsersFile("textFiles/premiumUsers.txt", ios::trunc);
            if (!premiumUsersFile) {
                cerr << "Error in opening all books file" << endl;
                return;
            }
    
            for (int i = 0; i < allUsers.size(); i++) {
                allUsers[i]->addUserToFile(premiumUsersFile);
            }
            premiumUsersFile.close();
        }

        else if (loginSystem.userType == 'N') {
            ofstream normalUserFile("textFiles/normalUsers.txt", ios::trunc);
            if (!normalUserFile) {
                cerr << "Error in opening all books file" << endl;
                return;
            }
    
            for (int i = 0; i < allUsers.size(); i++) {
                allUsers[i]->addUserToFile(normalUserFile);
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
        int available = 0;
        int numBooks = allBooks.size();
        for (int i = 0; i < numBooks; i++) {
            if (!allBooks[i].isBorrowed) {
                cout << allBooks[i];
                available++;
            }
        }
        if (available == 0)
            cout << "No books available" << endl;
    }

    int findBookIndex(string id) {
        for (int i = 0; i<allBooks.size(); i++) {
            if (allBooks[i].bookID == id) {
                return i;
            }
        }
        return -1;
    }

    void borrowBook(string idOfUser) { 
        string idToBorrow;

        int userIndex = loginedUserIndex(idOfUser);
        cout << "enter Book ID of book to borrow: ";
        cin.ignore();
        getline(cin, idToBorrow);
        int bookIndex = findBookIndex(idToBorrow);
        if (bookIndex == -1) {
            cout << "invalid id" << endl;
            return;
        }
        if (allUsers[userIndex]->isBookBorrowedByUser(idToBorrow) == true) {
            cout << "book already borrowed by you!" << endl;
            return;
        }
        if (allBooks[bookIndex].isBorrowed == true) {
            cout << "book already borrowed" << endl;
            return;
        }

        bool flag = allUsers[userIndex]->borrowBook(idToBorrow);  
        if (flag == true) {
            allBooks[bookIndex].borrowBook();
            saveBooks();
            saveUsers();
        }
    }

    void returnBook(string idOfUser) {
        string idToReturn;
        int userIndex = loginedUserIndex(idOfUser);
        cout << "enter Book ID of book to return: ";
        cin.ignore();
        getline(cin, idToReturn);
        int bookIndex = findBookIndex(idToReturn);
        if (bookIndex == -1) {
            cout << "invalid book id" << endl;
            return;
        }
        if (allBooks[bookIndex].isBorrowed == false) {
            cout << "book is not borrowed" << endl;
            return;
        }
        if (allUsers[userIndex]->isBookBorrowedByUser(idToReturn) == false) {
            cout << "this book is not borrowed by you!" << endl;
            return;
        }
        int daysOverDue = allBooks[bookIndex].getDaysOverdue();
        allUsers[userIndex]->calculateFine(daysOverDue);

        allBooks[bookIndex].returnBook(); 
        allUsers[userIndex]->returnBook(idToReturn);
        saveBooks();
        saveUsers();
    }

    void renewBook(string idOfUser) {
        char userType = idOfUser.at(0);
        string idToRenew;
        int userIndex = loginedUserIndex(idOfUser);
        cout << "enter Book ID of book to renew: ";
        cin.ignore();
        getline(cin, idToRenew);
        int bookIndex = findBookIndex(idToRenew);
        if (bookIndex == -1) {
            cout << "invalid book id" << endl;
            return;
        }
        if (allBooks[bookIndex].isBorrowed == false) {
            cout << "book is not borrowed" << endl;
            return;
        }
        if (allUsers[userIndex]->isBookBorrowedByUser(idToRenew) == false) {
            cout << "this book is not borrowed by you!" << endl;
            return;
        }
        int timesRenewed = allBooks[bookIndex].timesRenewed;
        if (userType == 'n' || userType == 'N') {
            if (timesRenewed == 1) {
                cout << "book has been renewed maximum times and cannot be renewed again" <<endl;
                return;
            }
        }

        if (userType == 'p' || userType == 'P') {
            if (timesRenewed == 3) {
                cout << "book has been renewed maximum times and cannot be renewed again" <<endl;
                return;
            }
        }

        allBooks[bookIndex].renew(); 
        saveBooks();
        saveUsers();
    }

    void payFine(string userID) {
        int userIndex = loginedUserIndex(userID);
        allUsers[userIndex]->payFine();
        saveUsers();
    }

    void deleteYourAccount() {
        bool flag = false;
        string userIdToRemove = loginSystem.loginedID;
        for (int i = 0; i < allUsers.size(); i++) {
            if (allUsers[i]->userID == userIdToRemove) {
                delete allUsers[i];
                allUsers.erase(allUsers.begin() + i);
                flag = true;
                ifstream inFile("textFiles/login.txt");
                ofstream outFile("textFiles/temp.txt");
                if (!inFile) {
                    cerr << "Error in opening login file" << endl;
                    return;
                }
                if (!outFile) {
                    cerr << "Error in opening temp file" << endl;
                    return;
                }
                string currentId;
                string password;
                bool removed = false;

                while (inFile >> currentId >> password) {
                    if (currentId == userIdToRemove) {
                        removed = true;
                    } 
                    else {
                        outFile << currentId << " " << password << endl;
                    }
                }
                inFile.close();
                outFile.close();

                if (removed) {
                    if (remove("textFiles/login.txt") != 0) {
                        cerr << "Error deleting original file." << endl;
                        return;
                    }
                    if (rename("textFiles/temp.txt", "textFiles/login.txt") != 0) {
                        cerr << "Error renaming temporary file." << endl;
                        return;
                    }
                    cout << "User " << userIdToRemove << " successfully removed." << endl;
                } 
                else {
                    remove("textFiles/temp.txt");
                    cout << "User " << userIdToRemove << " not found in the file." << endl;
                }
                break;
            }
        }
        if (flag == false) {
            cout << "Error in deleting your account" << endl;
        }
    }

    void displayUserBorrowedBooks(string userID) {
        int index = loginedUserIndex(userID);
        int numBooks = 0;
        const string* borrowedBooks = allUsers[index]->getBorrowedBooks();
        for (int i = 0; i < allUsers[index]->getMaxBooks(); i++) {
            if (borrowedBooks[i] != "x") {
                searchBookId(borrowedBooks[i]);
                numBooks++;
            }
        }
        if (numBooks == 0) {
            cout << "No Books Borrowed!" << endl;
        }
    }

    void LibrarianMenu(string userID) {
        int choice = -1;
        while(choice != 6) {
            cout << "\n1. search book\n2. view book list\n3. add new book to library\n4. remove a book\n5. delete your account\n6. logout\nenter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
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
                            string bookIDtoSearch;
                            cout << "enter book id to search: "; 
                            getline(cin, bookIDtoSearch);
                            searchBookId(bookIDtoSearch);
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

                case 3: { // add new book to library
                    string id, isbn, title, author, genre;
                    cout << "Enter book details of book to add" << endl;
                    cout << "Book ID: ";
                    cin.ignore();
                    getline(cin, id);
                    while (!isBookIDunique(id)) {
                        cout << "enter a unique book id: ";
                        getline(cin, id);
                    }
                    cout << "ISBN: ";
                    getline(cin, isbn);
                    cout << "Title: ";
                    getline(cin, title);
                    cout << "Author: ";
                    getline(cin, author);
                    cout << "Genre: ";
                    getline(cin, genre);
                    Book b1 = Book(id, isbn, title, author, genre);
                    allBooks.push_back(b1);
                    saveBooks();
                    break;
                }

                case 4: { // remove a book
                    string idToRemove;
                    bool flag = false;
                    cout << "enter book id of book to remove: ";
                    cin.ignore();
                    getline(cin, idToRemove);
                    for (int i = 0; i < allBooks.size(); i++) {
                        if (allBooks[i].bookID == idToRemove) {
                            allBooks.erase(allBooks.begin() + i);
                            cout << "book " << idToRemove << " removed successfully" << endl;
                            saveBooks();
                            flag = true;
                            break;
                        }
                    }
                    if (flag == false) {
                        cout << "book not found" << endl;
                    }
                    break;
                }

                case 5: {
                    deleteYourAccount();
                    saveUsers();
                    saveBooks();
                    loginSystem.logout();
                    break;
                }

                case 6: {
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

    void userMenu(string userID) {
        int choice = -1;
        while(choice != 9) {
            cout << "\n1. search book\n2. view book list\n3. borrow book\n4. return book\n5. pay fine\n6. renew book \n7. display books borrowed by you\n8. delete your account\n9. logout\nenter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: { 
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

            case 2: {
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

            case 3: {
                borrowBook(userID);
                break;
            }

            case 4: {
                returnBook(userID);
                break;
            }

            case 5: {
                cin.ignore();
                payFine(userID);
                break;
            }

            case 6: {
                renewBook(userID);
                break;
            }

            case 7: {
                displayUserBorrowedBooks(userID);
                break;
            }

            case 8: {
                bool finePaid = true, booksReturned = true;
                int indexOfUser = loginedUserIndex(userID);
                if (allUsers[indexOfUser]->getTotalFines() > 0) {
                    cout << "Outstanding fine: " << allUsers[indexOfUser]->getTotalFines() << endl;
                    cout << "pay fine to delete account!" << endl;
                    finePaid = false;
                }
                const string* borrowedBooks = allUsers[indexOfUser]->getBorrowedBooks();
                for (int i = 0; i < allUsers[indexOfUser]->getMaxBooks(); i++) {
                    if (borrowedBooks[i] != "x") {
                        booksReturned = false;
                    }
                }
                if (booksReturned == false) {
                    cout << "return all books to delete account!" << endl << "books currently borrowed by you:" << endl;
                    displayUserBorrowedBooks(userID);
                }
                if (finePaid == true && booksReturned == true) {
                    deleteYourAccount();
                    saveUsers();
                    saveBooks();
                    loginSystem.logout();
                }
                break;
            }
            
            case 9: {
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
        for (User* user : allUsers) { delete user; }
    }
};
#endif