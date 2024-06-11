#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

struct User {
    char username[50];
    char password[50];
};

class Movie {
public:
    string title;
    string showtime;
    double price;
    int availableSeats[10]; 

    Movie(string t, string s, double p) : title(t), showtime(s), price(p) {
        for (int i = 0; i < 10; ++i) {
            availableSeats[i] = 1; 
        }
    }
};

void registerUser(list<User>& users) {
    User* newUser = new User;
    cout << "Masukkan username: ";
    cin >> newUser->username;
    cout << "Masukkan password: ";
    cin >> newUser->password;
    users.push_back(*newUser);

    ofstream outFile("users.txt", ios::app);
    outFile << newUser->username << " " << newUser->password << endl;
    outFile.close();
    delete newUser;
}

bool loginUser(list<User>& users) {
    char username[50];
    char password[50];
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    for (User user : users) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            return true;
        }
    }
    return false;
}

void loadUsers(list<User>& users) {
    ifstream inFile("users.txt");
    if (!inFile) return;
    User user;
    while (inFile >> user.username >> user.password) {
        users.push_back(user);
    }
    inFile.close();
}
