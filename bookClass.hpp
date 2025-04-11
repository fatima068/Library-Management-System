#include <iostream>
#include <string>
using namespace std;

class Book {
    protected:
        const string bookID;
        string bookName;
        string authorName;
        string genre;
        bool borrowed;

    public:
        Book(string id) : bookID(id), bookName(""), authorName(""), genre(""), borrowed(false) {}

    Book(string id,string bookname, string authorname, string gen) : bookID(id), bookName(bookname), authorName(authorname), genre(gen) {
        borrowed = false;
        // yahin pe add this book to the file of its genre
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

void operator<< (ostream& COUT, Book& book) {
    COUT << "Book ID: " << book.getBookID() << ", Book Name: " << book.getBookName() << ", Author Name: " << book.getAuthorName() << ", Genre: " << book.getGenre() << ", Availability Status: ";
    if (book.getIsBorrowed() == true ) {
        cout << "notavailable" << endl;
    }
    else 
        cout << "available " << endl;
}