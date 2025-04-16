#ifndef BOOKCLASS_HPP
#define BOOKCLASS_HPP

#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include "system.hpp"   
#include "userClasses.hpp" 
using namespace std;

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

    Book(string bookID, string ISBN, string title, string author, string genre, bool isBorrowed, int day, int month, int year) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(isBorrowed), dueDate(day, month, year), timesRenewed(0) {
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
        allBooksFile << dueDate.dd << dueDate.mm << dueDate.yy << endl;
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
        return daysOverdue;
    }
        // if due date hasnt passed return 0, else return how many days have passed since due date, then in some other function apply fine according to user type
    

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

    friend void PremiumUser::renewBook(Book* b1);
    friend void NormalUser::renewBook(Book* b1);

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

#endif