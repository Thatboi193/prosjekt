#include <iostream>
#include <fstream>

using namespace std;

class User {
public:
    string name;
    double balance;

    void saveToFile() {
        ofstream outFile("users.txt", ios::app);  // Open file in append mode
        if (outFile.is_open()) {
            outFile << name << " " << balance << endl;  // Write name and balance to file
            outFile.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void makeUser() {
        cout << "Please enter Name and starting balance: " << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Balance: ";
        cin >> balance;
        saveToFile();  // Save user info to file after creating
    }

    void login() {
        string username;
        cout << "Login to account" << endl;
        cout << "Username: ";
        cin >> username;
        ifstream inFile("users.txt");  // Open file in read mode
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {  // Read file line by line
                if (line.find(username) != string::npos) {  // Check if username is found
                    cout << "Login successful" << endl;
                    name = username;  // Set name to the logged-in username
                    // Further processing to extract and set balance
                    break;
                }
            }
            inFile.close();
        } else {
            cout << "Unable to open file for reading." << endl;
        }
    }

    void deposit() {
        double newAmount;
        cout << "Add money to account balance" << endl;
        cin >> newAmount;
        balance += newAmount;
        cout << "New balance is " << balance << endl;
    }

    void withdraw() {
        double newAmount;
        cout << "Remove money from account balance" << endl;
        cin >> newAmount;
        balance -= newAmount;  // Corrected to subtract newAmount from balance
        cout << "New balance is " << balance << endl;
    }

    void fam() {
        int menu;
        cout << name << " Balance: " << balance << endl;  // Corrected to display name
        cout << "Type 1: for deposit 2: for withdraw 3: for show balance" << endl;
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "deposit" << endl;
                deposit();
                break;
            case 2:
                cout << "withdraw" << endl;
                withdraw();
                break;
            case 3:
                cout << "show balance: " << balance << endl;
                break;
        }
    }
};

int main() {
    User user1;
    user1.makeUser();
    user1.fam();

    return 0;
}
