#include <iostream>
#include <string>
#include <conio.h>  

using namespace std;

string getPassword() {
    string password;
    char ch;
    
    cout << "Enter password: ";
    
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key
    // jo input humne diya, usse getch se ch mei store kiya, then it checks ke enter key tou nai dabayi. if enter dabaya ho, exit loop. else check ke backspace tou press nai kiya. (if backpsapce, it takes it as inout so u need to handle it manually)

        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Move cursor back, overwrite with space, move back again
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

int main() {
    string password = getPassword();
    cout << "Your password is: " << password << endl;
    return 0;
}
