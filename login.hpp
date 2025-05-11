#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

class LoginSystem {
    private:
    char userType = 'X';
    bool loginStatus = 0;
    string loginedID = "X000";

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
        
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') { 
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; 
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
        // string encoded = "";
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
    
    bool login(string id) {
        ifstream loginFile;
        loginFile.open("textFiles/login.txt", ios::in);
        if (!loginFile.is_open()) {
            cout << "error in login file, try again later!" << endl;
            return 0;
        }
    
        // first search if id exists in the file
        // if id exists, compare passwords
        string fileID,  password, filePassword; 
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

    friend class System;
};