// hi can we like leave this cpp to test out dumm stuff plis fanks
#include <iostream>
#include <vector>
using namespace std;
// oke see this output aara bilkul sahi oki to aise hi karenge hum
class user {
    public:
    string name; 
    string id;  // oke this our class

    user(string n, string i) : name(n), id(i) {}
};

int main() { 
    user u1 = user("ikrash", "N000");
    user u2 = user("babar", "N001"); // these two are normal objects of the class
    vector<user*> allUsers; //same vector array from our fing
    user* loginedUser; // same pointer from our fing
    allUsers.push_back(&u1); 
    allUsers.push_back(&u2); // we put the basic objects in the vector array
 
    string id = "N001"; 
    for (int i = 0; i < allUsers.size(); i++) { 
        if (id == allUsers[i]->id) { // V
            loginedUser = allUsers[i];
            break;
        }
    }

    cout << loginedUser->name << endl << loginedUser->id <<endl << endl;
    loginedUser->name = "fakhar";
    cout << allUsers[1]->name << endl << allUsers[1]->id <<endl << endl;
}; 