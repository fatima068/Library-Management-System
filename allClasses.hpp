#ifndef ALLCLASSES_HPP
#define ALLCLASSES_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
// #include "system.hpp"
using namespace std;

class User;
class NormalUser;
class PremiumUser;

struct Date {
    int dd, mm, yy; // date format is dd-mm-yyyy (01-02-2024)

    Date(int d, int m, int y) : dd(d), mm(m), yy(y) {}
    Date() : dd(0), mm(0), yy(0) {}
};

Date dateTodayFunc() {
    time_t timeInSecondsToday = time(nullptr);
    tm* now = localtime(&timeInSecondsToday);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
} // this will return the date today
 // in system class, store todays date in a variable until program ends 

Date dateTodayVar = dateTodayFunc(); 
int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year) {
    if (year % 4 != 0) return false;       
    if (year % 100 != 0 || year % 400 == 0) return true;     
    return false;                          
}

// in compare date check if year is leap year and use 29 instead of 28 for daysInMonth[1]

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

    Book(string bookID, string ISBN, string title, string author, string genre, bool isBorrowed, int day, int month, int year, int timesRenewed) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(isBorrowed), dueDate(day, month, year), timesRenewed(timesRenewed) {}

    Book(string bookID, string ISBN, string title, string author, string genre, bool isBorrowed, int day, int month, int year) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(isBorrowed), dueDate(day, month, year), timesRenewed(0) {}

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
        // first compare year
        // then month
        // then day of the month
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
        // now all the cases have been covered where book has been returned on or before the due date
        // this means now we need to check ke book kitne din overdue hogai hai
    
        int daysOverdue, daysInDueMonth;
    
        if (dueDate.yy == dateTodayVar.yy && dueDate.mm == dateTodayVar.mm) {
            daysOverdue = dateTodayVar.dd - dueDate.dd;
            return daysOverdue;
        }
    
        // next condition will be when year is same but month is different
        if (dueDate.yy == dateTodayVar.yy) { 
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
    
        // now check when year is different too 
        // year is different 
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
        // if due date hasnt passed return 0, else return how many days have passed since due date, then in some other function apply fine according to user type
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
        return false; // fine will be calculated in user class ka return book 
    }

    bool borrowBook() {
        // first fetch data for that book from text file ???? or are we making aarrays in system class
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
            //update records in the file 
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
        // save data to file
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
        // save data to file
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

    friend class PremiumUser;
    friend class NormalUser;
    friend class System;
};

// instead of making display function here, do operator<< overloading to display book in system class

class User {
    protected:
    string userID;
    string name;
    string contactNum;

    public:
    User() : userID(""), name(""), contactNum("") {}

    User(string userID, string name, string contactNum) : userID(userID), name(name), contactNum(contactNum) {}

    // void setName(string n) {
    //     name = n;
    // }
    // void setContact(string c) {
    //     contactNum = c;
    // }

    virtual void borrowBook(string idToBorrow) = 0;
    virtual void returnBook(Book* b1) = 0;
    virtual bool addNewBook(Book b1) = 0;
    virtual bool removeBook(Book b1) = 0;
    virtual void renewBook(Book* b1) = 0;
    virtual void payFine() = 0;
    virtual void addUserToFile() =0;
    virtual void displayBooksBorrowed() = 0;
    virtual bool isBookBorrowed(string id) = 0;

    virtual ~User() = default;

    friend class System;
};

class PremiumUser: public User {
    protected:
    int maxBooks = 10; // use borrowed books.size() to get number of books currently borrowed by user
    string borrowedBooks[10] = {"x"}; 
    float finePer15Days = 5.0;
    float totalFines;

    public:
    PremiumUser() : User(), totalFines(0.0), borrowedBooks() {}

    PremiumUser(string userID, string name, string contactNum) : User(userID, name, contactNum), totalFines(0.0), borrowedBooks() {}

    // to create user object from information stored in premium file
    PremiumUser(string userID, string name, string contactNum, string arr[10], float totalFines) : User(userID, name, contactNum), maxBooks(10), finePer15Days(5.0), totalFines(totalFines)  {
        for (int i = 0; i < 10; i++) {
            borrowedBooks[i] = arr[i];
        }
    }

    void addUserToFile() override {
        ofstream premiumFile("textFiles/premiumUsers.txt", ios::app);
        if (!premiumFile) {
            cerr << "Error in opening all users file" << endl;
        }

        premiumFile << userID << endl;
        premiumFile << name << endl;
        premiumFile << contactNum << endl;
        for (int i = 0; i<10; i++) {
            premiumFile << borrowedBooks[i] << endl;
        }
        premiumFile << totalFines << endl;
        // after this, the file will store 1 user in 14 lines.
        premiumFile.close();
    }

    // void borrowBook(string idToBorrow) override {
    //     if (currentBooksBorrowed == maxBooks) {
    //         cout << "max borrowing limit reached. return a book to borrow a new one" << endl;
    //         return;
    //     }
    //     bool flag = b1->borrowBook();
    //     if (flag == true) {
    //         borrowedBooks.push_back(b1);
    //         currentBooksBorrowed++;
    //    }
    // }

    bool isBookBorrowedByUser(string idToBorrow) {
        for (int i = 0; i<10; i++) {
            if (idToBorrow == borrowedBooks[i]) {
                cout << "you have already borrowed this book!" << endl;
                return true;
            }
        }
        return false;
    }

    void borrowBook(string idToBorrow) override { // in system class, take input for id to borrow, find book from all books vector. first check if user has not already borrowed book. if not, call borrow book for book object, if it returns true, then call this function 
        if (borrowedBooks[9] != "x") {
            cout << "cannot borrow more books. limit reached" << endl;
            return;
        }
        bool flag = isBookBorrowedByUser(idToBorrow);
        if (flag == false) {
            for (int i = 0; i<10; i++) {
                if (borrowedBooks[i] == "x") {
                    borrowedBooks[i] = idToBorrow;
                    return;
                }
            }
        }
    }

    void returnBook(Book* b1) override {}
    bool isBookBorrowed(string id) override {}
    void renewBook(Book* b1) override {}

    // void returnBook(Book* b1) override {
    //     int index = -1;
    //     for (int i = 0; i<currentBooksBorrowed; i++) {
    //         if (borrowedBooks[i]->bookID == b1->bookID) {
    //             index = i;
    //             break;
    //         }
    //     }
    //     if (index == -1) {
    //         cout << "book " << b1->bookID << " not borrowed by user " << userID << endl;
    //         return;
    //     }
    //     bool flag = b1->returnBook();
    //     if (flag) {
    //         int daysOverdue = b1->getDaysOverdue();
    //         if (daysOverdue >= 15) {
    //             float fine = (daysOverdue/15) * finePer15Days;
    //             totalFines += fine;
    //         }
    //     }
    //     borrowedBooks.erase(borrowedBooks.begin() + index);
    //     currentBooksBorrowed--;
    // }

    // bool isBookBorrowed(string id) override {
    //     for (int i = 0; i < borrowedBooks.size(); i ++) {
    //         if (id == borrowedBooks[i]->bookID) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }

    // void renewBook(Book* b1) override {
    //     if (b1->timesRenewed == 3) {
    //         cout << "book cannot be renewed again! limit is reached" << endl;
    //         return;
    //     }
    //     b1->renew();
    // }

    void payFine() override {
        float amt;
        cout << "Total Fines: " << totalFines << endl;
        cout << "enter amount of fine to pay: ";
        cin >> amt;
        totalFines -= amt;
        cout << "fine amount " << amt << " paid for user: " << userID << endl;
    }

    bool addNewBook(Book b1) override {
        cout << "User cannot add new book"<< endl;
        return false;
    }

    bool removeBook(Book b1) override {
        cout << "user cannot remove book" << endl;
        return false;
    }

    void displayBooksBorrowed() override { 
        cout << "List of Borrowed Books: " << endl; //um idk maybe change the wordings here
            // for (int i = 0; i < borrowedBooks.size(); i++) {
            //     cout << i << ") " << borrowedBooks[i];
            // }
    }

    // friend ostream& operator<< (ostream& out, PremiumUser p1) {
    //     out << "User Type: Premium User" << endl; 
    //     out << "User ID: " << p1.userID<< endl << "Name: " << p1.name << endl << "Contact Number: " << p1.contactNum << endl << "Total Fine: " << p1.totalFines << endl << "Number of Books Currently Borrowed: " << p1.borrowedBooks.size() << endl;
    //     if (p1.borrowedBooks.size() > 0) {
    //         out << "List of Borrowed Books: " << endl;
    //         for (int i = 0; i < p1.borrowedBooks.size(); i++) {
    //             out << i << ") " << p1.borrowedBooks[i];
    //             // ya to we do upar wali fing or i was finking ke yahan pe maybe lets only output the index number and the book name worr do u say
    //         }
    //     }
    //     return out;
    // }

    friend class System;
};

class NormalUser: public User {
    protected:
    int maxBooks = 3;
    string borrowedBooks[3] = {"x"}; 
    float finePerDay = 0.5;
    float totalFines;

    public:
    NormalUser() : User(), totalFines(0.0), borrowedBooks() {}

    NormalUser(string userID, string name, string contactNum) : User(userID, name, contactNum), totalFines(0.0), borrowedBooks() {}

    //constructor to create object after reading data from file
    NormalUser(string userID, string name, string contactNum, string arr[3], float totalFines) : User(userID, name, contactNum), maxBooks(3), finePerDay(0.5), totalFines(totalFines) {}

    void addUserToFile() override {
        ofstream normalFile("textFiles/normalUsers.txt", ios::app);
        if (!normalFile) {
            cerr << "Error in opening all users file" << endl;
        }

        normalFile << userID << endl;
        normalFile << name << endl;
        normalFile << contactNum << endl;
        for (int i=0; i<3; i++) {
            normalFile << borrowedBooks[i] << endl;
        }
        normalFile << totalFines << endl;
        // after this, the file will store 1 user in 7 lines. 
        normalFile.close();
    }

    bool isBookBorrowedByUser(string idToBorrow) {
        for (int i = 0; i<3; i++) {
            if (idToBorrow == borrowedBooks[i]) {
                cout << "you have already borrowed this book!" << endl;
                return true;
            }
        }
        return false;
    }

    void borrowBook(string idToBorrow) override { // in system class, take input for id to borrow, find book from all books vector. first check if user has not already borrowed book. if not, call borrow book for book object, if it returns true, then call this function 
        if (borrowedBooks[2] != "x") {
            cout << "cannot borrow more books. limit reached" << endl;
            return;
        }
        bool flag = isBookBorrowedByUser(idToBorrow);
        if (flag == false) {
            for (int i = 0; i<3; i++) {
                if (borrowedBooks[i] == "x") {
                    borrowedBooks[i] = idToBorrow;
                    return;
                }
            }
        }
    }

    void returnBook(Book* b1) override {
    //     int index = -1;
    //     for (int i = 0; i<currentBooksBorrowed; i++) {
    //         if (borrowedBooks[i]->bookID == b1->bookID) {
    //             index = i;
    //             break;
    //         }
    //     }
    //     if (index == -1) {
    //         cout << "book " << b1->bookID << " not borrowed by user " << userID << endl;
    //         return;
    //     }
    //     bool flag = b1->returnBook();
    //     if (flag) {
    //         int daysOverdue = b1->getDaysOverdue();
    //         if (daysOverdue >= 15) {
    //             float fine = daysOverdue * finePerDay;
    //             totalFines += fine;
    //         }
    //     }
    //     borrowedBooks.erase(borrowedBooks.begin() + index);
    //     currentBooksBorrowed--;
    }

    bool isBookBorrowed(string id) override {
    //     for (int i = 0; i < borrowedBooks.size(); i ++) {
    //         if (id == borrowedBooks[i]->bookID) {
    //             return true;
    //         }
    //     }
    //     return false;
    }

    void renewBook(Book* b1) override {
    //     if (b1->timesRenewed == 1) {
    //         cout << "book cannot be renewed again! limit is reached" << endl;
    //         return;
    //     }
    //     b1->renew();
    }

    void payFine() override {
        float amt;
        cout << "Total Fines: " << totalFines << endl;
        cout << "enter amount of fine to pay: ";
        cin >> amt;
        totalFines -= amt;
        cout << "fine amount " << amt << " paid for user: " << userID << endl;
    }

    bool addNewBook(Book b1) override {
        cout << "User cannot add new book"<< endl;
        return false;
    }

    bool removeBook(Book b1) override {
        cout << "user cannot remove book" << endl;
        return false;
    }

    void displayBooksBorrowed() override { 
    //     cout << "List of Borrowed Books: " << endl; //um idk maybe change the wordings here
    //         for (int i = 0; i < currentBooksBorrowed; i++) {
    //             cout << i << ") " << borrowedBooks[i];
    //         }
    }

    friend ostream& operator<< (ostream& out, NormalUser n1) {
        out << "User Type: Normal User" << endl; 
        out << "User ID: " << n1.userID<< endl << "Name: " << n1.name << endl << "Contact Number: " << n1.contactNum << endl << "Total Fine: " << n1.totalFines << endl;
        if (n1.borrowedBooks[0] != "x") {
            out << "List of Borrowed Books: " << endl;
            for (int i = 0; i < 3; i++) {
                if (n1.borrowedBooks[0] != "x") {
                    out << i << ". " << n1.borrowedBooks[i]; // maybe only output due date and book name here (is book id needed ? ) right now it will output only the book id. Make a function get book or something to search book from allbooks vector using the given bookid
                }
            }
        }
        else cout << "no books currently borrowed by user"<< endl;
        return out;
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

    void addUserToFile() override {
        ofstream librariansFile("textFiles/librarians.txt", ios::app);
        if (!librariansFile) {
            cerr << "Error in opening all users file" << endl;
        }

        librariansFile << userID << endl;
        librariansFile << name << endl;
        librariansFile << contactNum << endl;
        librariansFile << monthlySalary << endl;
        // after this, the file will store 1 user in 4 lines. 
        librariansFile.close();
    }

    void borrowBook(string idToBorrow) override {
        cout << "librarian cant borrow/return books" << endl;
    }

    void returnBook(Book* b1) override {
        cout << "librarian cant borrow/return books" << endl;         
    }

    void renewBook(Book* b1) override {
        cout << "action cannot be performed by librarian " << endl;
    }

    void payFine() override {
        cout << "action cannot be performed by librarian " << endl;
    }

    bool addNewBook(Book b1) {
        cout << "Librarian " << userID << " attempting to add book" << endl;
        return true;
    }

    bool removeBook(Book b1) {
        cout << "Librarian " << userID << " attempting to add book" << endl;
        return true;
    }

    // system class mei for user* object, call this function, if it returns true add book else user cannot add book

    friend ostream& operator<< (ostream& out, Librarian l1) {
        out << "User Type: Librarian" << endl; 
        out << "User ID: " << l1.userID << endl << "Name: " << l1.name << endl << "Contact Number: " << l1.contactNum << endl << "Monthly Salary: " << l1.monthlySalary <<  endl;
        return out;
    }

    virtual void displayBooksBorrowed() override {
        cout << "not a valid librarian operation" << endl;
    }

    virtual bool isBookBorrowed (string id) override {
        cout << "not a valid librarian function" << endl;
        return false;
    }

    friend class System;
};
#endif

/* 
OKE     to we need to see loading user abhi na

no wait pehle lets figure out the outline of the program (oki)

id say 
we make ek vector of user class  iska load karna about the vector<string> borrowedBooks in user class i was thinking ke what we do is: 
    id tou agai na books ki
    tou like if user wants to return a book 
    we hata usski id from user ka object 
    but then we go to books array
    and udhr se we find our desired book id
    and we do 
    if (id == allBooks[i].bookID) {
        allBooks[i].returnBook();
    }
    but for this hume user class mei function rewrite karne parenge and also change systen class accordingly 


     
ek vector of book\
matlab load dono ka shit from files haina
then user type ajayega login ke baad 
tou acording to user type we load the appropriate file to a vector 
then logined user nikalen uss se
then uss  logined user pe saare operation perform karen

*/