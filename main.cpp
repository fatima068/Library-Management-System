#include <iostream>
#include "login.hpp"
#include "bookClass.hpp"
using namespace std;

int main () {
    Book b1 = Book("B001", "percy jackson", "rick", "mythology");
    cout << b1;

    // bool loginStatus = login(); 
    // while (loginStatus == 1){
    //     switch (userType) {
    //         case 'L':
    //             // librarian function
    //             break;
    //         case 'P':
    //             // premium user function 
    //             break;
    //         case 'N':
    //             // normal user function 
    //             break;
    //         default:
    //             break;
    //     }
    // }
}

