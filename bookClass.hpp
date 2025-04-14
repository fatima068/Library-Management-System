#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Date {
    int dd, mm, yy; // date format is dd-mm-yyyy (01-02-2024)

    Date(int d, int m, int y) : dd(d), mm(m), yy(y) {}
};

Date dateTodayFunc() {
    time_t timeInSecondsToday = time(nullptr);
    tm* now = localtime(&timeInSecondsToday);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
} // this will return the date today
 // in system class, store todays date in a variable until program ends 

Date dateTodayVar = dateTodayFunc(); 

bool isLeapYear(int year) {
    if (year % 4 != 0) return false;       
    if (year % 100 != 0 || year % 400 == 0) return true;     
    return false;                          
}

// in compare date check if year is leap year and use 29 instead of 28 for daysInMonth[1]                      

int compareDate(Date bookDue) {
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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
        string bookName;
        string authorName;
        string genre;
        bool borrowed;
        string dateBorrowed;

    public:
    Book(string id) : bookID(id), bookName(""), authorName(""), genre(""), borrowed(false), dateBorrowed("") {}

    Book(string id,string bookname, string authorname, string gen, string dateBorrowed) : bookID(id), bookName(bookname), authorName(authorname), genre(gen), dateBorrowed(dateBorrowed), borrowed(false) {
        // yahin pe add this book to the file of its genre
        // also add book to allBooks text file
        // have 5 genres: mystery, classic, fiction, autobiography, fantasy
    }

    string getBookID() const {
        return bookID;
    }
    string getBookName() const {
        return bookName;
    }
    string getAuthorName() const {
        return authorName;
    }
    string getGenre() const {
        return genre;
    }
    bool getIsBorrowed() const {
        return borrowed;
    }

    void toggleAvailability() {
        borrowed = (!borrowed);
    }
};

// after leraning friend function, try doing overloading fing inside class to avoid making getters

// main mei when book display karna ho, just cout it, no need to make display function.

// void operator<< (ostream& COUT, Book& book) {
//     COUT << "Book ID: " << book.getBookID() << ", Book Name: " << book.getBookName() << ", Author Name: " << book.getAuthorName() << ", Genre: " << book.getGenre() << ", Availability Status: ";
//     if (book.getIsBorrowed() == true ) {
//         cout << "notavailable" << endl;
//     }
//     else 
//         cout << "available " << endl;
// }