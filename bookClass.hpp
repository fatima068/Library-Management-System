#include <iostream>
#include <string>
#include <ctime>
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

int compareDate(Date bookDue) {
    // first compare year
    // then month
    // then day of the month
    if (bookDue.yy > dateTodayVar.yy) {
        return 0;
    }
    if (bookDue.yy == dateTodayVar.yy && bookDue.mm > dateTodayVar.mm) {
        return 0;
    }

    if (bookDue.yy == dateTodayVar.yy && bookDue.mm == dateTodayVar.mm && bookDue.dd > dateTodayVar.dd) {
        return 0;
    }

    if (bookDue.yy == dateTodayVar.yy && bookDue.mm == dateTodayVar.mm && bookDue.dd == dateTodayVar.dd) {
        return 0; 
    }
    // now all the cases have been covered where book has been returned on or before the due date
    // this means now we need to check ke book kitne din overdue hogai hai

    int daysOverdue, daysInDueMonth;

    if (bookDue.yy == dateTodayVar.yy && bookDue.mm == dateTodayVar.mm) {
        daysOverdue = dateTodayVar.dd - bookDue.dd;
        return daysOverdue;
    }

    // next condition will be when year is same but month is different
    if (bookDue.yy == dateTodayVar.yy) { 
        daysInDueMonth = daysInMonth[bookDue.mm - 1];
        if (bookDue.mm == 2 && isLeapYear(bookDue.yy)) { 
            daysInDueMonth = 29;
        }
        // Days remaining in due month after due date
        daysOverdue = daysInDueMonth - bookDue.dd;     
        // Add all full months between due month and current month
        for (int month = bookDue.mm + 1; month < dateTodayVar.mm; month++) {
            daysOverdue += daysInMonth[month - 1];
            if (month == 2 && isLeapYear(bookDue.yy)) {
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
    daysInDueMonth = daysInMonth[bookDue.mm - 1];
    if (bookDue.mm == 2 && isLeapYear(bookDue.yy)) {
        daysInDueMonth = 29;
    }
    daysOverdue = daysInDueMonth - bookDue.dd;

    // Part B: Remaining months in due year
    for (int month = bookDue.mm + 1; month <= 12; month++) {
        daysOverdue += daysInMonth[month - 1];
        if (month == 2 && isLeapYear(bookDue.yy)) {
            daysOverdue += 1;
        }
    }
    
    // Part C: Full years between due year and current year
    for (int year = bookDue.yy + 1; year < dateTodayVar.yy; year++) {
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

class Book {
    protected:
        const string bookID;
        const string ISBN;
        string title;
        string author;
        string genre;
        bool isBorrowed;
        Date dueDate;

    public:
    Book() : bookID(""), ISBN(""), title(""), author(""), genre(""), isBorrowed(false), dueDate() {}

    Book(string bookID, string ISBN, string title, string author, string genre, bool isBorrowed, int day, int month, int year) : bookID(bookID), ISBN(ISBN), title(title), author(author), genre(genre), isBorrowed(isBorrowed), dueDate(day, month, year) {
        // add book to file here i think ? because new book object has been created and should be added to all books file and genre specific file too 
    }

    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            dueDate.dd = 0; dueDate.mm = 0; dueDate.yy = 0;
            cout << title <<" returned successfully" << endl;
            return;
        }
        cout << "book is not borrowed" << endl; // fine will be calculated in user class ka return book 
    }

    void borrowBook() {
        if(isBorrowed) {
            cout << "book already borrowed by other user" << endl;
            return;
        }
        isBorrowed = true;
        int dueDay = dateTodayVar.dd + 14; 
        int dueMonth = dateTodayVar.mm; 
        int dueYear = dateTodayVar.yy; 
        int daysThisMonth = daysInMonth[dateTodayVar.mm-1];

        if (dueDay <= daysThisMonth) {
            dueDate = Date(dueDay, dueMonth, dueYear);
            cout << "book borrowed with due date: " << dueDay << "." << dueMonth << "." << dueYear << endl; 
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
    }
};

// instead of making display function here, do operator<< overloading to display book in system class