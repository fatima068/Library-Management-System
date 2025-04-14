#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
using namespace std;

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
        // open file 
        ifstream loginFile;
        loginFile.open("textFiles/login.txt", ios::in);
        if (!loginFile.is_open()) {
            cout << "error in login file, try again later!" << endl;
            return 0;
        }
    
        // first search if id exists in the file
        // if id exists, compare passwords
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
        
        // if passwords match, give appropriate access to users (add functionality in main function menu)
        return 0;
    }
    
    void logout() {
        userType = 'X';
        loginStatus = 0;
        cout << "logging out and exiting....";
        exit(0);
    }
};

// sign out function mei make login status 0 and usertype X again (isske liye login.hpp ko signout.hpp mei imclude karna parega)

// password input karte huey try doing it in the form ***** or .....

// login jab hojaye tou go to all users waali file, read uss user ka data from there and store it in object or pointer of user class, then call usske function waghera and logout karte huey update usska data in the file taake wo save hojaye kyunke object/pointer tou main band karne ke baad delete hojayega