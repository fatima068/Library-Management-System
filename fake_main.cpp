#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// elloooooooo

class System;

// Book class and related code
struct Date {
    int dd, mm, yy; // date format is dd-mm-yyyy (01-02-2024)

    Date(int d, int m, int y) : dd(d), mm(m), yy(y) {}
    Date() : dd(0), mm(0), yy(0) {}
};

Date dateTodayFunc() {
    time_t timeInSecondsToday = time(nullptr);
    tm* now = localtime(&timeInSecondsToday);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

Date dateTodayVar = dateTodayFunc(); 
int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year) {
    if (year % 4 != 0) return false;       
    if (year % 100 != 0 || year % 400 == 0) return true;     
    return false;                          
}

class Book { 
    protected:
        const string bookID;
        const string ISBN;
        string title;
        string author;
        string genre;
        bool isBorrowed;
        Date dueDate;
        int timesRenewed;

    public:
    Book() : bookID(""), ISBN(""), title(""), author(""), genre(""), isBorrowed(false), dueDate(), timesRenewed(0) {}

    // Getters
    string getBookID() const { return bookID; }
    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    bool getIsBorrowed() const { return isBorrowed; }
    Date getDueDate() const { return dueDate; }
    int getTimesRenewed() const { return timesRenewed; }

    // Setters
    void setTitle(const string& newTitle) { title = newTitle; }
    void setAuthor(const string& newAuthor) { author = newAuthor; }
    void setGenre(const string& newGenre) { genre = newGenre; }
    void setIsBorrowed(bool borrowed) { isBorrowed = borrowed; }
    void setDueDate(const Date& newDueDate) { dueDate = newDueDate; }
    void setTimesRenewed(int times) { timesRenewed = times; }

    Book(string bookID, string ISBN, string title, string author, string genre, bool isBorrowed, int day, int month, int year) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(isBorrowed), dueDate(day, month, year), timesRenewed(0) {
        // ofstream allBooksFile("textFiles/allBooks.txt", ios::app);
        // if (!allBooksFile) {
        //     cerr << "Error in opening all books file" << endl;
        // }

        // allBooksFile << bookID << endl;
        // allBooksFile << ISBN << endl;
        // allBooksFile << title << endl;
        // allBooksFile <<  author << endl;
        // allBooksFile << genre << endl; 
        // if (isBorrowed) allBooksFile << "true\n";
        // else allBooksFile << "false\n";
        // allBooksFile << dueDate.dd << endl;
        // allBooksFile << dueDate.mm << endl;
        // allBooksFile << dueDate.yy << endl;
        // allBooksFile << timesRenewed << endl;
        // allBooksFile.close();
    }

    int getDaysOverdue() {
        if (dueDate.yy > dateTodayVar.yy) {
            return 0;
        }
        if (dueDate.yy == dateTodayVar.yy && dueDate.mm > dateTodayVar.mm) {
            return 0;
        }
    
        if (dueDate.yy == dateTodayVar.yy && dueDate.mm == dateTodayVar.mm && dueDate.dd > dateTodayVar.dd) {
            return 0;
        }
    
        if (dueDate.yy == dateTodayVar.yy && dueDate.mm == dateTodayVar.mm && dueDate.dd == dateTodayVar.dd) {
            return 0; 
        }
    
        int daysOverdue, daysInDueMonth;
    
        if (dueDate.yy == dateTodayVar.yy && dueDate.mm == dateTodayVar.mm) {
            daysOverdue = dateTodayVar.dd - dueDate.dd;
            return daysOverdue;
        }
    
        if (dueDate.yy == dateTodayVar.yy) { 
            daysInDueMonth = daysInMonth[dueDate.mm - 1];
            if (dueDate.mm == 2 && isLeapYear(dueDate.yy)) { 
                daysInDueMonth = 29;
            }
            daysOverdue = daysInDueMonth - dueDate.dd;     
            for (int month = dueDate.mm + 1; month < dateTodayVar.mm; month++) {
                daysOverdue += daysInMonth[month - 1];
                if (month == 2 && isLeapYear(dueDate.yy)) {
                    daysOverdue += 1;
                }
            }      
            daysOverdue += dateTodayVar.dd;     
            return daysOverdue;
        }
    
        daysInDueMonth = daysInMonth[dueDate.mm - 1];
        if (dueDate.mm == 2 && isLeapYear(dueDate.yy)) {
            daysInDueMonth = 29;
        }
        daysOverdue = daysInDueMonth - dueDate.dd;
    
        for (int month = dueDate.mm + 1; month <= 12; month++) {
            daysOverdue += daysInMonth[month - 1];
            if (month == 2 && isLeapYear(dueDate.yy)) {
                daysOverdue += 1;
            }
        }
        
        for (int year = dueDate.yy + 1; year < dateTodayVar.yy; year++) {
            if (isLeapYear(year)) {
                daysOverdue += 366;
            } else {
                daysOverdue += 365;
            }
        } 
    
        for (int month = 1; month < dateTodayVar.mm; month++) {
            daysOverdue += daysInMonth[month - 1];
            if (month == 2 && isLeapYear(dateTodayVar.yy)) {
                daysOverdue += 1;
            }
        }
    
        daysOverdue += dateTodayVar.dd;
        return daysOverdue;
    }

    bool returnBook() {
        if (isBorrowed) {
            isBorrowed = false; 
            dueDate.dd = 0; dueDate.mm = 0; dueDate.yy = 0;
            timesRenewed = 0; 
            cout << bookID <<" returned successfully" << endl;
            return true;
        }
        cout << "book is not borrowed" << endl; 
        return false;
    }

    bool borrowBook() {
        if(isBorrowed) {
            cout << "book already borrowed by other user" << endl;
            return false;
        }
        isBorrowed = true;
        int dueDay = dateTodayVar.dd + 14; 
        int dueMonth = dateTodayVar.mm; 
        int dueYear = dateTodayVar.yy; 
        int daysThisMonth = daysInMonth[dateTodayVar.mm-1];

        if (dueDay <= daysThisMonth) {
            dueDate = Date(dueDay, dueMonth, dueYear);
            cout << "book " << bookID << " borrowed with due date: " << dueDay << "." << dueMonth << "." << dueYear << endl; 
            return true;
        }

        if (dueDay > daysThisMonth) {
            dueDay = dueDay - daysThisMonth;
            dueMonth++;
        }
        if (dueMonth > 12) {
            dueMonth = 1;
            dueYear++;
        }

        dueDate = Date(dueDay, dueMonth, dueYear);
        cout << "book borrowed with due date: " << dueDay << "." << dueMonth << "." << dueYear << endl; 
        return true;
    }

    bool renew() {
        if (!isBorrowed) {
            cout << "book is not borrowed" << endl; 
            return false;
        }

        if (getDaysOverdue() > 0) {
            cout << "book can not be renewed after passing of due date" << endl;
            return false;
        }

        int dueDay = dueDate.dd + 14; 
        int dueMonth = dueDate.mm; 
        int dueYear = dueDate.yy; 
        int daysThisMonth = daysInMonth[dueDate.mm-1];

        if (dueDay > daysThisMonth) {
            dueDay = dueDay - daysThisMonth;
            dueMonth++;
        }
        if (dueMonth > 12) {
            dueMonth = 1;
            dueYear++;
        }

        dueDate = Date(dueDay, dueMonth, dueYear);
        timesRenewed++;
        cout << "book renewed with due date: " << dueDay << "." << dueMonth << "." << dueYear << endl; 
        return true;
    }

    friend ostream& operator<< (ostream& out, Book &b1) {
        out << "Book ID: " << b1.bookID << endl << "Book title: " << b1.title << endl << "Author: " << b1.author << endl << "Genre: " << b1.genre << "ISBN: " << b1.ISBN << endl;
        if (b1.isBorrowed) {
            out << "Status: Unavailable" << endl;
            out << "Due Date: " << b1.dueDate.dd << "." << b1.dueDate.mm << "." << b1.dueDate.yy << endl;
            out << "Times Renewed: " << b1.timesRenewed << endl;
        } 
        else {
            out << "Status: Available" << endl;
        }
        return out;
    }

    friend class System;
};

// User classes
class User {
    protected:
    const string userID;
    string name;
    string contactNum;

    public:
    User() : userID(""), name(""), contactNum("") {}

    User(string userID, string name, string contactNum) : userID(userID), name(name), contactNum(contactNum) {}

    void setName(string n) {
        name = n;
    }
    void setContact(string c) {
        contactNum = c;
    }

    virtual void borrowBook(Book* b1) = 0;
    virtual void returnBook(Book* b1) = 0;
    virtual void editUserInfo(User* u1) = 0;
    virtual void setNewFine(float amt) = 0;
    virtual bool addNewBook(Book b1) = 0;
    virtual bool removeBook(Book b1) = 0;
    virtual void renewBook(Book* b1) = 0;

    virtual ~User() = default;

    friend class System;
};

class PremiumUser: public User {
    protected:
    const int maxBooks = 10;
    int currentBooksBorrowed;
    vector<Book*> borrowedBooks; 
    const float finePer15Days = 5.0;
    float totalFines;

    public:
    PremiumUser() : User(), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    PremiumUser(string userID, string name, string contactNum) : User(userID, name, contactNum), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    void setNewFine(float amt) override {
        totalFines = totalFines - amt;
    }

    void borrowBook(Book* b1) override {
        if (currentBooksBorrowed == maxBooks) {
            cout << "max borrowing limit reached. return a book to borrow a new one" << endl;
            return;
        }
        bool flag = b1->borrowBook();
        if (flag == true) {
            borrowedBooks.push_back(b1);
            currentBooksBorrowed++;
       }
    }

    void returnBook(Book* b1) override {
        int index = -1;
        for (int i = 0; i<currentBooksBorrowed; i++) {
            if (borrowedBooks[i]->getBookID() == b1->getBookID()) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "book " << b1->getBookID() << " not borrowed by user " << userID << endl;
            return;
        }
        bool flag = b1->returnBook();
        if (flag) {
            int daysOverdue = b1->getDaysOverdue();
            if (daysOverdue >= 15) {
                float fine = (daysOverdue/15) * finePer15Days;
                totalFines += fine;
            }
        }
        borrowedBooks.erase(borrowedBooks.begin() + index);
        currentBooksBorrowed--;
    }

    void renewBook(Book* b1) override {
        if (b1->getTimesRenewed() == 3) {
            cout << "book cannot be renewed again! limit is reached" << endl;
            return;
        }
        b1->renew();
    }

    void editUserInfo(User* u1) override {
        cout << "User cant edit users info" << endl;
    }

    bool addNewBook(Book b1) override {
        cout << "User cannot add new book"<< endl;
        return false;
    }

    bool removeBook(Book b1) override {
        cout << "user cannot remove book" << endl;
        return false;
    }

    friend class System;
};

class NormalUser: public User {
    protected:
    const int maxBooks = 3;
    vector<Book*> borrowedBooks; 
    int currentBooksBorrowed;
    const float finePerDay = 0.5;
    float totalFines;

    public:
    NormalUser() : User(), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    NormalUser(string userID, string name, string contactNum) : User(userID, name, contactNum), currentBooksBorrowed(0), totalFines(0.0), borrowedBooks() {}

    void setNewFine(float amt) override {
        totalFines = totalFines - amt;
    }

    void borrowBook(Book* b1) override {
        if (currentBooksBorrowed == maxBooks) {
            cout << "max borrowing limit reached. return a book to borrow a new one" << endl;
            return;
        }
        bool flag = b1->borrowBook();
        if (flag == true) {
            borrowedBooks.push_back(b1);
            currentBooksBorrowed++;
       }
    }

    void returnBook(Book* b1) override {
        int index = -1;
        for (int i = 0; i<currentBooksBorrowed; i++) {
            if (borrowedBooks[i]->getBookID() == b1->getBookID()) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "book " << b1->getBookID() << " not borrowed by user " << userID << endl;
            return;
        }
        bool flag = b1->returnBook();
        if (flag) {
            int daysOverdue = b1->getDaysOverdue();
            if (daysOverdue >= 15) {
                float fine = daysOverdue * finePerDay;
                totalFines += fine;
            }
        }
        borrowedBooks.erase(borrowedBooks.begin() + index);
        currentBooksBorrowed--;
    }

    void renewBook(Book* b1) override {
        if (b1->getTimesRenewed() == 1) {
            cout << "book cannot be renewed again! limit is reached" << endl;
            return;
        }
        b1->renew();
    }

    void editUserInfo(User* u1) {
        cout << "User cant edit users info" << endl;
    }

    bool addNewBook(Book b1) override {
        cout << "User cannot add new book"<< endl;
        return false;
    }

    bool removeBook(Book b1) override {
        cout << "user cannot remove book" << endl;
        return false;
    }

    friend class System;
};

class Librarian : public User {
    protected:
    float monthlySalary;

    public:
    Librarian() : User(), monthlySalary(0.0) {}

    Librarian(string userID, string name, string contactNum, float monthlySalary) : User(userID, name, contactNum), monthlySalary(monthlySalary) {}

    void borrowBook(Book* b1) override {
        cout << "librarian cant borrow/return books" << endl;
    }

    void returnBook(Book* b1) override {
        cout << "librarian cant borrow/return books" << endl;
    }

    void renewBook(Book* b1) override {
        cout << "action cannot be performed by librarian " << endl;
    }

    void setNewFine(float amt) override {}

    bool addNewBook(Book b1) {
        cout << "Librarian " << userID << " attempting to add book" << endl;
        return true;
    }

    bool removeBook(Book b1) {
        cout << "Librarian " << userID << " attempting to add book" << endl;
        return true;
    }

    void editUserInfo(User* u1) override {
        int choice;
        cout << "Editing user info: " << endl;
        cout << "1. name\n2. contact number\n3. pay user fine\n4. exit" << endl;
        cin >> choice;

        switch(choice) {
            case 1:{
                string newName;
                cout << "enter new name: ";
                getline(cin, newName);
                u1->setName(newName);
                break;
            }

            case 2:{
                string newContact;
                cout << "enter new contact: ";
                getline(cin, newContact);
                u1->setContact(newContact);
                break;
            }
        }
    }
};

// Login system
class LoginSystem {
    private:
    char userType = 'X';
    bool loginStatus = 0;

    public:

    char getUserType() const {
        return userType;
    }
    bool getLoginStatus() const {
        return loginStatus;
    }

    string getPassword() {
        string password;
        char ch;
        
        cout << "Enter password: ";
        
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') { 
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; 
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        return password;
    }
    
    void encode(string& password) {
        string encoded = "";
        for (int i=0; i<password.length(); i++){
            if (password.at(i) >= 65 && password.at(i) <= 89){
                password.at(i)++;
            }
            if (password.at(i) >= 97 && password.at(i) <= 121){
                password.at(i)++;
            }
            if (password.at(i) == 122){
                password.at(i)  = 97;
            }
            if (password.at(i) == 90){
                password.at(i) = 65;
            }
        }
    }
    
    bool login() {
        ifstream loginFile;
        loginFile.open("textFiles/login.txt", ios::in);
        if (!loginFile.is_open()) {
            cout << "error in login file, try again later!" << endl;
            return 0;
        }
    
        string fileID, id, password, filePassword;
        cout << "enter id: ";
        cin >> id;
        password = getPassword();
    
        while (loginFile >> fileID >> filePassword) {
            if (fileID == id) {
                encode(password);
                if (filePassword == password) {
                    cout << "login successful! " << endl;
                    userType = id.at(0);
                    return 1;
                }
            }
        }
        cout << "login details invalid! " << endl;
        loginFile.close();
        return 0;
    }
    
    void logout() {
        userType = 'X';
        loginStatus = 0;
        cout << "logging out and exiting....";
        exit(0);
    }
};

// System class
class System {
    private:
    vector<User*> allUsers;
    vector<Book> allBooks;

    public:
    void display() {
        cout << allBooks[0];
    }

    void addBookToFile(Book b1) {
        ofstream allBooksFile("textFiles/allBooks.txt", ios::app);
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
        }

        allBooksFile << b1.bookID << endl;
        allBooksFile << b1.ISBN << endl;
        allBooksFile << b1.title << endl;
        allBooksFile <<  b1.author << endl;
        allBooksFile << b1.genre << endl; 
        if (b1.isBorrowed) allBooksFile << "true\n";
        else allBooksFile << "false\n";
        allBooksFile << b1.dueDate.dd << endl;
        allBooksFile << b1.dueDate.mm << endl;
        allBooksFile << b1.dueDate.yy << endl;
        allBooksFile << b1.timesRenewed << endl;
        allBooksFile.close();
    }

    void searchBookName() {
        string nameToSearch;
        cout << "enter book name to search: ";
        cin >> nameToSearch;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].getTitle() == nameToSearch) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }

    void searchAuthorName() {
        string authorToSearch;
        cout << "enter author to search: ";
        cin >> authorToSearch;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].getTitle() == authorToSearch) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }

    void searchBookId() {
        string is_default_constructible;
        cout << "enter book id to search: ";
        cin >> is_default_constructible;
        int numBooks = allBooks.size(); 
        bool flag = false;
        for (int i = 0; i < numBooks; i++) {
            if (allBooks[i].getTitle()== is_default_constructible) {
                cout << allBooks[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no book found" << endl;
        }
    }
    
    void searchUserName() {
        string nameToSearch;
        cout << "enter user name to search: ";
        cin >> nameToSearch;
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->name == nameToSearch) {
                cout << allUsers[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl;
        } 
    }
    
    void searchUserId() {
        string idToSearch;
        cout << "enter user name to search: ";
        cin >> idToSearch;
        int numUsers = allUsers.size(); 
        bool flag = false;
        for (int i = 0; i < numUsers; i++) {
            if (allUsers[i]->userID == idToSearch) {
                cout << allUsers[i];
                flag = true;
            }
        }
        if (!flag) {
            cout << "no user found" << endl;
        } 
    }

    User* findUser(const string& userID) {
        for (User* user : allUsers) {
            if (user->userID == userID) {
                return user;
            }
        }
        return nullptr;
    }

    void loadBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }
        bool success = true;
        string bookData[10];  // Stores: bookid, isbn, title, author, genre, borrow, dd, mm, yy, timesRenewed
        while (1) {
            if (!getline(allBooksFile, bookData[0])) {
                success = false;
            }

            if (success == false) {
                cout << "all books read from file to vector" << endl;
                return;
            }
            
            // Read all 9 fields for a single book
            cout << "reading fields from file to vector" << endl;
            for (int i = 1; i < 10; i++) {
                if (getline(allBooksFile, bookData[i])) {
                    success = false;
                    break;
                }
            }
    
            // Parse fields with error handling
            bool borrow = (bookData[5] == "true");  // borrow status ("true"/"false")
    
            int dd = 0, mm = 0, yy = 0, timesRenewed = 0;
            try {
                dd = stoi(bookData[6]);    // Day
                mm = stoi(bookData[7]);    // Month
                yy = stoi(bookData[8]);   // Year
                timesRenewed = stoi(bookData[9]); // timesRenewed
            } catch (...) {
                cerr << "Warning: Invalid number format in book entry. Using default values (0)." << endl;
                // Default values (0) already set
            }
    
            // Create and store the book
            Book temp = Book(bookData[0], bookData[1], bookData[2], bookData[3], bookData[4], borrow, dd, mm, yy);
            allBooks.push_back(temp);
            getline(allBooksFile, bookData[0]);
        }
        allBooksFile.close();
    }
    
    // void loadBooks() {
    //     ifstream allBooksFile("textFiles/allBooks.txt");
    //     if (!allBooksFile) {
    //         cerr << "Error in opening all books file" << endl;
    //         return;
    //     }

    //     string line, bookid, isbn, title, author, genre;
    //     int dd, mm, yy, timesRenewed;
    //     bool borrow;
    //     while (getline(allBooksFile, line)) {  
    //         bookid = line;
            
    //         getline(allBooksFile, line);  
    //         isbn = line;
            
    //         getline(allBooksFile, line);  
    //         title = line;
            
    //         getline(allBooksFile, line);  
    //         author = line;
            
    //         getline(allBooksFile, line);  
    //         genre = line;
            
    //         getline(allBooksFile, line);
    //         borrow = (line == "true");
            
    //         getline(allBooksFile, line);
    //         dd = stoi(line);
            
    //         getline(allBooksFile, line);
    //         mm = stoi(line);
            
    //         getline(allBooksFile, line);
    //         yy = stoi(line);

    //         getline(allBooksFile, line);  
    //         timesRenewed = stoi(line);
            
    //         Book temp = Book(bookid, isbn, title, author, genre, borrow, 0, 0, 0);
    //         allBooks.push_back(temp);
    //     }
    //     allBooksFile.close();
    // }

    void saveBooks() {
        ifstream allBooksFile("textFiles/allBooks.txt");
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
            return;
        }

        allBooksFile.close();
    }

    void LibrarianMenu() {
        int choice = -1;
        while(choice != 8) {
            cout << "1. search book\n2. search user\n3. delete a user account\n4. view book list\n5. add new book to library\n6. remove a book\n 7. edit user info\n8. exit\nenter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    int choice; 
                    cout << "1. by book name\n2. by author name\n3. by book id\nenter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            searchBookName();
                            break;
                        }
                        case 2: {
                            searchAuthorName();
                            break;
                        }
                        case 3: {
                            searchBookId();
                            break;
                        }
                        default:
                            cout << "wrong input dumbass" << endl;
                            break;
                    }
                    break;
                }

                case 2: {
                    int choice; 
                    cout << "1. by user name\n2. by book id\nenter your choice: ";
                    cin >> choice;
                    switch (choice) {
                        case 1: {
                            searchUserName(); 
                            break;
                        }

                        case 2: {
                            searchUserId();
                            break;
                        }
                    }
                }
            }
        }
    }

    void userMenu() {
        // Implement user menu functionality
    }

    ~System() {
        for (User* user : allUsers) {
            delete user;
        }
    }
};

int main() {
    System librarySystem;
    
    Book testBook("B001", "9783161484100", "Sample Book", "Test Author", "Fiction", false, 0, 0, 0);
    
    // Load initial data
    librarySystem.loadBooks();
    cout << "trying to display vector" << endl;
    librarySystem.display();
    cout << "hogya display vector";

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