#include <iostream>
#include "system.hpp"
using namespace std;

int main() {
    // System librarySystem;
    // librarySystem.mainMenu();
    User* u1 = new PremiumUser("N100", "fatima", "0330");
    User* u2 = new Librarian("L100", "fama", "03322", 50000.0);

}

//oke so abhi we havent done this but
//first we'll make an object of loginsystem, and then we ask for an id from user
//we pass that id into login() and get a true or false of if valid, haina
//so then if false we'll be like bruh give a correct password
//if true to we have to see what type of user has logined
//to i finking, we make some function in system class, where we pass the id and we find id from the array and store everything from there to the pointer logined user (pssss i made a function in system, i.e. logAUser(string id) )
//this will make our life very very easier pleaseeeeee