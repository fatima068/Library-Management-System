#ifndef ALLCLASSES_HPP
#define ALLCLASSES_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

struct Date {
    int dd, mm, yy; // date format is dd-mm-yyyy (01-02-2024)

    Date(int d, int m, int y) : dd(d), mm(m), yy(y) {}
    Date() : dd(0), mm(0), yy(0) {}
};

Date dateTodayFunc() { // this function returns current date
    time_t timeInSecondsToday = time(nullptr);
    tm* now = localtime(&timeInSecondsToday);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
} // call this function and store current date in a global variable until program ends 

Date dateTodayVar = dateTodayFunc(); 
int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year) {
    if (year % 4 != 0) return false;       
    if (year % 100 != 0 || year % 400 == 0) return true;     
    return false;
}

class Book { 
    protected:
    string bookID;
    string ISBN;
    string title;
    string author;
    string genre;
    bool isBorrowed;
    Date dueDate;
    int timesRenewed;

    public:
    Book() : bookID(""), ISBN(""), title(""), author(""), genre(""), isBorrowed(false), dueDate(), timesRenewed(0) {}

    Book(string bookID, string ISBN, string title, string author, string genre, bool isBorrowed, int day, int month, int year, int timesRenewed) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(isBorrowed), dueDate(day, month, year), timesRenewed(timesRenewed) {} // create an object of book after reading data from file

    Book(string bookID, string ISBN, string title, string author, string genre) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(false), dueDate(), timesRenewed(0) {} // paramterized constructor to create a new book object 

    void addBookToFile() {
        ofstream allBooksFile("textFiles/allBooks.txt", ios::app);
        if (!allBooksFile) {
            cerr << "Error in opening all books file" << endl;
        }

        allBooksFile << bookID << endl;
        allBooksFile << ISBN << endl;
        allBooksFile << title << endl;
        allBooksFile <<  author << endl;
        allBooksFile << genre << endl; 
        if (isBorrowed) allBooksFile << "true\n";
        else allBooksFile << "false\n";
        allBooksFile << dueDate.dd << endl;
        allBooksFile << dueDate.mm << endl;
        allBooksFile << dueDate.yy << endl;
        allBooksFile << timesRenewed << endl;
        allBooksFile.close();
    }

    int getDaysOverdue() { 
         if (dueDate.yy > dateTodayVar.yy || (dueDate.yy == dateTodayVar.yy && dueDate.mm > dateTodayVar.mm) || (dueDate.yy == dateTodayVar.yy && dueDate.mm == dateTodayVar.mm && dueDate.dd >= dateTodayVar.dd)) { 
            return 0;
        }  // all the cases where book has been returned on/before the due date have been checked. Calculate days overdue now
    
        int daysOverdue=0, daysInDueMonth;
    
        if (dueDate.yy == dateTodayVar.yy && dueDate.mm == dateTodayVar.mm) { // current year & month and year & month of due date is same
            daysOverdue = dateTodayVar.dd - dueDate.dd;
            return daysOverdue;
        }
    
        if (dueDate.yy == dateTodayVar.yy) { // year is same, month is different
            daysInDueMonth = daysInMonth[dueDate.mm - 1];
            if (dueDate.mm == 2 && isLeapYear(dueDate.yy)) { 
                daysInDueMonth = 29;
            }
            // Days remaining in due month after due date
            daysOverdue = daysInDueMonth - dueDate.dd;     
            // Add all full months between due month and current month
            for (int month = dueDate.mm + 1; month < dateTodayVar.mm; month++) {
                daysOverdue += daysInMonth[month - 1];
                if (month == 2 && isLeapYear(dueDate.yy)) {
                    daysOverdue += 1; // Add extra day for leap February
                }
            }      
            // Add days passed in current month
            daysOverdue += dateTodayVar.dd;     
            return daysOverdue;
        }
    
        // if year is different
        // Part A: Days remaining in due month
        daysInDueMonth = daysInMonth[dueDate.mm - 1];
        if (dueDate.mm == 2 && isLeapYear(dueDate.yy)) {
            daysInDueMonth = 29;
        }
        daysOverdue = daysInDueMonth - dueDate.dd;
    
        // Part B: Remaining months in due year
        for (int month = dueDate.mm + 1; month <= 12; month++) {
            daysOverdue += daysInMonth[month - 1];
            if (month == 2 && isLeapYear(dueDate.yy)) {
                daysOverdue += 1;
            }
        }
        
        // Part C: Full years between due year and current year
        for (int year = dueDate.yy + 1; year < dateTodayVar.yy; year++) {
            if (isLeapYear(year)) {
                daysOverdue += 366;
            } else {
                daysOverdue += 365;
            }
        } 
    
        // Part D: Months in current year before current month
        for (int month = 1; month < dateTodayVar.mm; month++) {
            daysOverdue += daysInMonth[month - 1];
            if (month == 2 && isLeapYear(dateTodayVar.yy)) {
                daysOverdue += 1;
            }
        }
    
        // Part E: Days in current month
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

    void borrowBook() {
        isBorrowed = true;
        int dueDay = dateTodayVar.dd + 14; 
        int dueMonth = dateTodayVar.mm; 
        int dueYear = dateTodayVar.yy; 
        int daysThisMonth = daysInMonth[dateTodayVar.mm-1];

        if (dueDay <= daysThisMonth) {
            dueDate = Date(dueDay, dueMonth, dueYear);
            cout << "book " << bookID << " borrowed with due date: " << dueDay << "." << dueMonth << "." << dueYear << endl; 
            return;
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
        return;
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
        out << "Book ID: " << b1.bookID << ", Book title: " << b1.title << ", Author: " << b1.author << ", Genre: " << b1.genre << ", ISBN: " << b1.ISBN;
        if (b1.isBorrowed) {
            out << ", Status: Unavailable";
            out << ", Due Date: " << b1.dueDate.dd << "." << b1.dueDate.mm << "." << b1.dueDate.yy;
            out << ", Times Renewed: " << b1.timesRenewed << endl;
        } 
        else { out << ", Status: Available" << endl; }
        return out;
    }

    friend class PremiumUser;
    friend class NormalUser;
    friend class System;
};

class User {
    protected:
    string userID;
    string name;
    string contactNum;

    public:
    User() : userID(""), name(""), contactNum("") {}

    User(string userID, string name, string contactNum) : userID(userID), name(name), contactNum(contactNum) {}

    virtual bool borrowBook(string idToBorrow) = 0;
    virtual void returnBook(string idToReturn) = 0;
    virtual void payFine() = 0;
    virtual void addUserToFile(ofstream& filep) = 0; 
    virtual bool isBookBorrowedByUser(string id) = 0;
    virtual void calculateFine(int daysOverDue) = 0;
    virtual float getTotalFines() = 0;
    virtual const string* getBorrowedBooks() const = 0;
    virtual int getMaxBooks() = 0;
    virtual ~User() = default;

    friend class System;
};

class PremiumUser: public User {
    protected:
    int maxBooks = 10;
    string borrowedBooks[10] = {"x", "x", "x", "x", "x", "x", "x", "x", "x", "x"}; 
    float finePer15Days = 5.0;
    float totalFines;

    public:
    PremiumUser() : User(), totalFines(0.0) {}

    PremiumUser(string userID, string name, string contactNum) : User(userID, name, contactNum), totalFines(0.0) {}

    // to create user object from information stored in premium file
    PremiumUser(string userID, string name, string contactNum, string arr[10], float totalFines) : User(userID, name, contactNum), maxBooks(10), finePer15Days(5.0), totalFines(totalFines)  {
        for (int i = 0; i < 10; i++) {
            borrowedBooks[i] = arr[i];
        }
    }

    float getTotalFines()override { return totalFines;}

    void addUserToFile(ofstream& filep) override{
        filep << userID << endl;
        filep << name << endl;
        filep << contactNum << endl;
        for (int i=0; i<10; i++) {
            filep << borrowedBooks[i] << endl;
        }
        filep << totalFines << endl;
    }

    bool isBookBorrowedByUser(string idToBorrow) {
        for (int i = 0; i<10; i++) {
            if (idToBorrow == borrowedBooks[i]) {
                return true;
            }
        }
        return false;
    }

    bool borrowBook(string idToBorrow) override {
        if (borrowedBooks[9] != "x") {
            cout << "cannot borrow more books. limit reached" << endl;
            return false;
        }
        for (int i = 0; i<10; i++) {
            if (borrowedBooks[i] == "x") {
                borrowedBooks[i] = idToBorrow;
                return true;
            }
        }
        return false;
    }

    void payFine() override {
        if (totalFines > 0) {
            char choice;
            cout << "Total Fines: " << totalFines << endl;
            cout << "would you like to pay (y for Yes, n for No): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                totalFines = 0.0;
                cout << "All fine cleared. \nTotal Fines: " << totalFines << endl;
                return;
            }
            if (choice == 'n' || choice == 'N') {
                cout << "returning to User Menu.." << endl;
                return;
            }
            cout << "Invalid input! returning to User Menu" << endl;
            return;
        }
        else cout << "total fine = 0" << endl;
    } 

    void returnBook(string idToReturn) { 
       int index = -1;
       for (int i = 0; i<10; i++) {
            if (borrowedBooks[i] == idToReturn) {
                index = i;
                break;
            }
        }
        for (int i = index; i < 9; i++) {
            borrowedBooks[i] = borrowedBooks[i + 1]; 
        }
        borrowedBooks[9] = "x";
    }

    void calculateFine(int daysOverDue) override {
        float fine = 0.0;
        if (daysOverDue >= 15) {
             fine = daysOverDue % 15 * finePer15Days;
        }
        totalFines += fine;
        cout << "fine of rs " << fine << ", new total fines are: rs " << totalFines << endl;
    }

    const string* getBorrowedBooks() const override { return borrowedBooks; }
    int getMaxBooks() override { return maxBooks; }

    friend class System;
};

class NormalUser: public User {
    protected:
    int maxBooks = 3;
    string borrowedBooks[3] = {"x", "x", "x"}; 
    float finePerDay = 0.5;
    float totalFines;

    public:
    NormalUser() : User(), totalFines(0.0) {}

    NormalUser(string userID, string name, string contactNum) : User(userID, name, contactNum), totalFines(0.0) {}

    NormalUser(string userID, string name, string contactNum, string arr[3], float totalFines) : User(userID, name, contactNum), maxBooks(3), finePerDay(0.5), totalFines(totalFines) { //constructor to create object after reading data from file
        for (int  i = 0; i < 3; i++) {
            borrowedBooks[i] = arr[i];
        }
    }

    float getTotalFines() override {return totalFines;}

    void addUserToFile(ofstream& filep) override {
        filep << userID << endl;
        filep << name << endl;
        filep << contactNum << endl;
        for (int i=0; i<3; i++) {
            filep << borrowedBooks[i] << endl;
        }
        filep << totalFines << endl;
    }

    bool isBookBorrowedByUser(string idToBorrow) {
        for (int i = 0; i<3; i++) {
            if (idToBorrow == borrowedBooks[i]) {
                return true;
            }
        }
        return false;
    }

    bool borrowBook(string idToBorrow) override { // in system class, take input for id to borrow, find book from all books vector. first check if user has not already borrowed book. if not, call borrow book for book object, if it returns true, then call this function 
        if (borrowedBooks[2] != "x") {
            cout << "cannot borrow more books. limit reached" << endl;
            return false;
        }
        for (int i = 0; i<3; i++) {
            if (borrowedBooks[i] == "x") {
                borrowedBooks[i] = idToBorrow;
                return true;
            }
        }
        return false;
    }

    void returnBook(string idToReturn) override {
        int index = -1;
        for (int i = 0; i<3; i++) {
            if (borrowedBooks[i] == idToReturn) {
                index = i;
                break;
            }
        }
        for (int i = index; i < 2; i++) {
            borrowedBooks[i] = borrowedBooks[i + 1];
        }
        borrowedBooks[2] = "x";
    }

    void calculateFine(int daysOverDue) override {
        float fine = 0;
        fine = daysOverDue * finePerDay;
        totalFines += fine;
        cout << "fine of rs " << fine << ", new total fines: " << totalFines << endl;
    }

    const string* getBorrowedBooks() const override { return borrowedBooks; }

    int getMaxBooks() override { return maxBooks; }

    void payFine() override {
        if (totalFines > 0) {
            char choice;
            cout << "Total Fines: " << totalFines << endl;
            cout << "would you like to pay (y for Yes, n for No): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                totalFines = 0.0;
                cout << "All fine cleared. \nTotal Fines: " << totalFines << endl;
                return;
            }
            if (choice == 'n' || choice == 'N') {
                cout << "returning to User Menu" << endl;
                return;
            }
            cout << "Invalid input! returning to User Menu" << endl;
            return;
        }
        cout << "All fines have been paid" << endl;
    }

    friend class System;
};

class Librarian : public User {
    protected:
    float monthlySalary;

    public:
    Librarian() : User(), monthlySalary(0.0) {}

    // constructor to create object after reading data from file 
    Librarian(string userID, string name, string contactNum, float monthlySalary) : User(userID, name, contactNum), monthlySalary(monthlySalary) {}

    void addUserToFile(ofstream& filep) override {
        filep << userID << endl;
        filep << name << endl;
        filep << contactNum << endl;
        filep << monthlySalary << endl;
    }

    float getTotalFines() override { 
        cout << "not a valid librarian function " << endl;
        return 0.0; 
    }

    const string* getBorrowedBooks() const override {
        cout << "not a valid librarian function " << endl;
        return nullptr;
    }

    int getMaxBooks() override { return 0; }

    bool borrowBook(string idToBorrow) override { cout << "librarian cant borrow/return books" << endl; return false; }

    void returnBook(string idToReturn) override { cout << "librarian cant borrow/return books" << endl;}

    void payFine() override { cout << "not a valid librarian function " << endl; }

    bool isBookBorrowedByUser(string id) override {
        cout << "not a valid librarian function " << endl;
        return false;
    }

    void calculateFine(int daysOverDue) override { cout << "not a valid librarian function " << endl; }
};
#endif